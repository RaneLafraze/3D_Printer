#include "G1.h"
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
 */
void G1::execute(String line)
{
	double *currentPos = machine->getPosition();
	double targetPos[3];
	double maxTravel = 0.0;

	std::map<char, double> parameters;
	char identifier = 'X';
	double value = 0.0;
	int spaceIndex = line.indexOf(" ");
	String part = "";

	// Validate
	part = line.substring(0, spaceIndex);
	if(part != tag)
	{
		// If it doesn't equal the tag, something went wrong, so exit
		return;
	}

	// Move past the command tag
	spaceIndex = line.indexOf(" ", spaceIndex + 1);

	// Populate parameters map
	while(spaceIndex != -1)
	{
		// If there is a trailing space, continue parsing
		if(line.indexOf(" ", spaceIndex + 1))
		{
			part = line.substring(spaceIndex, line.indexOf(" ", spaceIndex + 1));
		} else // Otherwise use the \n character to finish
		{
			part = line.substring(spaceIndex, line.indexOf("\n"));
		}

		identifier = line.charAt(0);
		value = atof(line.substring(1, line.length()).c_str()); // Convert to double

		parameters.insert(std::pair<char, double>(identifier, value));

		spaceIndex = line.indexOf(" ", spaceIndex + 1);
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

}



