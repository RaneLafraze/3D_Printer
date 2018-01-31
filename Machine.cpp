#include "Machine.h"
#include "commands/CommandBase.hpp"
#include "Global.h"

Machine::Machine()
{

	gcode = "";
}

Machine::~Machine()
{
}

/**
 * Creates all of the commands for the entire
 * g-code content. It pushes each new command
 * to the back of the commands deque, and the
 * commands are pointers.
 */
void Machine::parseGcode()
{
	String cleaned = removeComments(gcode);
	int lastIndex = 0;
	int counter = 0;

	// Find how many new lines there are
	while(lastIndex != -1)
	{
		lastIndex = cleaned.indexOf("\n", lastIndex);

		if(lastIndex != -1)
		{
			lastIndex++; // Prevent from re-counting the same sequence
			counter++;
		}
	}

	// +1 in case there is no end line at the end of file
	// Better to be over than under
	parseGcode(counter + 1, 0);

}

/**
 * Loads the number of lines of commands after skipping
 * the offset. NOTE: offset is in terms of only NEW LINE
 * characters, not just any text characters. If
 * the line count, or offset values are too low,
 * this method will do nothing. If they are too
 * high, it will return the maximum number of commands.
 * Therefore, it is better to have high values instead
 * of low ones.
 */
void Machine::parseGcode(int lineCount, int offset)
{
	String cleaned = removeComments(gcode);

	String tag = "";
	String commandTags[lineCount]; // May not be needed
	int beginIndex = 0;
	int spaceIndex = 0;

	if(lineCount <= 0) return;
	if(offset < 0) return;

	for(int f = 0; f < getArraySize(commandTags); f++)
	{
		commandTags[f] = "";
	}

	for(int s = 0; s < offset; s++)
	{
		beginIndex = cleaned.indexOf("\n", beginIndex);
		if(beginIndex != -1)
		{
			beginIndex++;
		} else
		{
			break; // End the loop
		}
	}

	for(int i = 0; i < lineCount; i++)
	{
		if(beginIndex != -1)
		{
			spaceIndex = cleaned.indexOf(" ", beginIndex);
			// Command may be followed by a new line instead of space
			if(spaceIndex == -1) spaceIndex = cleaned.indexOf("\n", beginIndex);
			// There may not be a new line at the end of the file
			if(spaceIndex == -1) spaceIndex = cleaned.length();

			if(spaceIndex != -1)
			{
				tag = cleaned.substring(beginIndex, (spaceIndex - beginIndex));

				beginIndex = cleaned.indexOf("\n", beginIndex);
				if(beginIndex != -1) beginIndex++;
				if(tag.length() != 0)
				{
					commandTags[i] = tag;
					commands.push_back(Global::cmdManager.getCommand(tag));
				}
			}

		} else
		{
			break;
		}
	}

	//return commandTags;
}

/**
 * Generates and returns a double array defining the position of
 * the head on the machine (x, y, z).
 *
 * @return
 * A pointer to the double array of the 3 axis positions.
 */
double* Machine::getPosition()
{
	double pos[3];

	pos[0] = xAxis.getPosition();
	pos[1] = yAxis.getPosition();
	pos[2] = zAxis.getPosition();

	return pos;
}

/**
 * Removes all comments from the g-code. Comments
 * begin with ";"
 */
String Machine::removeComments(String raw)
{

	int lastIndex = 0;
	int endIndex = 0;

	while(lastIndex != -1)
	{
		lastIndex = raw.indexOf(";");
		endIndex = raw.indexOf("\n", lastIndex);

		if((lastIndex != -1) && (endIndex != -1))
		{
			raw = raw.substring(0, (unsigned)lastIndex) + raw.substring((unsigned)endIndex);
		}
	}

	return raw;
}

int Machine::getArraySize(String array[])
{
	// 24 seems to be the "magic" number
	return sizeof(array) / 24;
}

// Get / Set methods

String Machine::getGcode()
{
	return gcode;
}
void Machine::setGcode(String arg_gcode)
{
	gcode = arg_gcode;
}

