#include "G1.h"
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

G1::~G1() {

}

/**
 * This will run this command. It will perform the operations within
 * the Machine via the Machine pointer defined in the constructor. The
 * line variable should INCLUDE the command tag.
 * TESTED: 1/10/18
 */
void G1::execute(String line)
{
	double *currentPos = machine->getPosition();
//	double maxTravel = 0.0; // ??
	std::map<char, double> parameters;

	char identifier = 'X';
	double value = 0.0;
	size_t spaceIndex = line.indexOf(" "); // Acts as the "cursor"
	String part = "";

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
			identifier = part.charAt(0);
			value = atof(part.substring(1, part.length()).c_str()); // Convert to double

			parameters.insert(std::pair<char, double>(identifier, value));

			spaceIndex = line.indexOf(" ", spaceIndex + 1);
		} else
		{
			spaceIndex++; // To avoid infinite loops
		}
	}

	// Compute the desired position
	// --X--
	if(parameters.find('X') != parameters.end())
	{
		targetPos[0] = parameters.find('X')->second;
	} else
	{
		// Else use existing position (no change)
		targetPos[0] = currentPos[0];
	}

	// --Y--
	if(parameters.find('Y') != parameters.end())
	{
		targetPos[1] = parameters.find('Y')->second;
	} else
	{
		targetPos[1] = currentPos[1];
	}

	// --Z--
	if(parameters.find('Z') != parameters.end())
	{
		targetPos[2] = parameters.find('Z')->second;
	} else
	{
		targetPos[2] = currentPos[2];
	}

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



}



