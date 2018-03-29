#include "G1.h"
#include "../Utility.hpp"
#include <math.h>
#include <map>

G1::G1(String arg_name, String arg_tag, Machine *arg_machine)
		: CommandBase(arg_name, arg_tag, arg_machine)
{

}

G1::G1(String arg_tag, Machine *arg_machine) : CommandBase(arg_tag, arg_machine)
{
	name = "G1";
}

G1::~G1()
{

}


/**
 * This will run this command. It will perform the operations within
 * the Machine via the Machine pointer defined in the constructor. The
 * line variable should INCLUDE the command tag.
 * TESTED: 3/28/18
 */
void G1::execute(String line)
{
	double *currentPos = machine->getPosition();
//	double maxTravel = 0.0; // ??
	std::map<char, double> parameters;
	double feedrate = Configuration::MAX_FEEDRATE; // Speed: units/mn

	char identifier = 'x';
	double value = 0.0;
	size_t spaceIndex = line.indexOf(" "); // Acts as the "cursor"
	String part = "";

	double largestMove = 0.0;
	char largestAxis = 'X';

	// Validate
	if(line.indexOf(tag) == -1)
	{
		// If the tag was not found, something went wrong, so exit
		return;
	} else
	{
		spaceIndex = line.indexOf(" ", line.indexOf(tag));
	}

	// Populate parameters map
	while(spaceIndex != std::string::npos)
	{
		// If there is a trailing space, continue parsing
		if(line.indexOf(" ", spaceIndex + 1))
		{
			part = line.substring(spaceIndex + 1, line.indexOf(" ", spaceIndex + 1));
		} else // Otherwise use the \n character to finish
		{
			part = line.substring(spaceIndex, line.indexOf("\n"));
		}

		if(part.length() > 0)
		{
			identifier = part.charAt(0); // X, Y, Z, E, etc.
			value = atof(part.substring(1, part.length()).c_str()); // Convert to double

			parameters.insert(std::pair<char, double>(identifier, value));

			spaceIndex = line.indexOf(" ", spaceIndex + 1);
		} else
		{
			spaceIndex++; // To avoid infinite loops
		}
	}

	// Compute the desired position
	// --X, Y, Z, E--
	for(int a = 0; a < 4; a++)
	{
		char id = 'X';
		switch(a)
		{
			case 0:
				id = 'X';
				break;
			case 1:
				id = 'Y';
				break;
			case 2:
				id = 'Z';
				break;
			case 3:
				id = 'E';
				break;
		}

		// Make sure there is a value for the given axis
		if(parameters.find(id) != parameters.end())
		{
			// Round the target to the nearest 1,000th place
			targetPos[a] = Utility::roundToPlace(parameters.find(id)->second, 1000);

			// Update largest move
			if(Utility::absFixed(currentPos[a] - targetPos[a]) > largestMove)
			{
				largestMove = Utility::absFixed(currentPos[a] - targetPos[a]);
				largestAxis = id;
			}
		} else
		{
			targetPos[a] = currentPos[a];
		}

	}

	/*
	 * A note about feedrate; RepRap states that, in a G1 command, the F
	 * flag indicates that the feedrate should slowly accelerate along
	 * with the other axis. However, for simplicity, I'm just setting the
	 * feedrate for now. This could be changed in the future to improve
	 * prints.
	 */

	// --F-- (Feedrate)
	if(parameters.find('F') != parameters.end())
	{
		feedrate = parameters.find('F')->second;
	}
	if((feedrate > Configuration::MAX_FEEDRATE) || (feedrate <= 0))
	{
		feedrate = Configuration::MAX_FEEDRATE;
	}
	machine->setFeedrate(feedrate);

	// --S-- (End stop check)
	if((parameters.find('S') != parameters.end()) && (parameters.find('S')->second == 1.0))
	{
		checkEndstop = true;
	} else
	{
		checkEndstop = false;
	}


	// Compute time for longest move
	// TODO: Implement feedrate variable instead of MIN_STEPPER_DELAY
	double moveTime = 0.0;
	if(machine->getAxis(largestAxis)->getUnits() == Configuration::MM)
	{
		moveTime = largestMove / Configuration::MM_PER_STEP * Configuration::MIN_STEPPER_DELAY;
	} else if(machine->getAxis(largestAxis)->getUnits() == Configuration::IN)
	{
		moveTime = largestMove / Configuration::IN_PER_STEP * Configuration::MIN_STEPPER_DELAY;
	} else
	{
		// Dummy value, hope it works if ever need be
		moveTime = largestMove * Configuration::MIN_STEPPER_DELAY;
	}

	// Compute the increment times
	for(int a = 0; a < 4; a++) // 4 axis
	{
		// Make sure it's not 0, which would lead to a divide error
		if((currentPos[a] - targetPos[a]) != 0)
		{
			// TODO: Make sure abs() doesn't cause rounding problems
			incrementDelays[a] = moveTime / Utility::absFixed(currentPos[a] - targetPos[a]) / 200;
		} else
		{
			incrementDelays[a] = 0.0;
		}
	}

	for(int p = 0; p < 4; p++)
	{
		startPos[p] = currentPos[p];
	}
	startTime = millis();
	isRunning = true;

}

/**
 * This should be called in a loop. It will take care of movement and
 * the updating of this command and the values concerning the operations.
 * It should also end the command by setting isRunning to false.
 *
 * @param delta
 * the time since the last update
 */
void G1::update(long delta)
{
	double *currentPos = machine->getPosition();
	unsigned long currentTime = millis();
	int finishedCount = 0;

	// Move the axis if they haven't reached the target destination yet
	for(int a = 0; a < 4; a++)
	{
		// If it's time for the motor to move
		if(currentTime - startTime > incrementDelays[a] * Utility::absFixed(startPos[a] - currentPos[a]))
		{
			if((checkEndstop) && (getAxisByNum(a)->readEndStopPin()))
			{
				// If end-stop checking is enabled and the end-stop has
				// been triggered, skip this axis.
				finishedCount++;
				continue;
			}

			// Move the axis toward the target
			if(currentPos[a] < targetPos[a])
			{
				getAxisByNum(a)->moveOneStep(1);
			} else if(currentPos[a] > targetPos[a])
			{
				getAxisByNum(a)->moveOneStep(-1);
			}  else // Increment the finish count because the goal was met
			{
				finishedCount++;
			}
		} // End of time if statement
	}

	if(finishedCount == 4) // If all axis have finished
	{
		isRunning = false;
	}

}

/**
 * Returns the axis that is represented by the given number. This method
 * allows tasks involving all four axis to be executed in a for
 * loop. The mappings are:  0: X,  1: Y,  2: Z,  3: E
 *
 * @param num
 * the number of the desired axis
 * @return
 * The axis that is paired with the given value.
 */
Axis* G1::getAxisByNum(int num)
{
	switch(num)
	{
		case 0:
			return machine->getAxis('X');
			break;
		case 1:
			return machine->getAxis('Y');
			break;
		case 2:
			return machine->getAxis('Z');
			break;
		case 3:
			return machine->getAxis('E');
			break;
	}
	// If all else fails, return the X axis
	return machine->getAxis('X');
}


