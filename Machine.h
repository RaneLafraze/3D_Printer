#ifndef MACHINE_H_
#define MACHINE_H_

//#include "commands/CommandBase.hpp"
#include "Axis.h"

#include <deque>
#include "Arduino.h"

class CommandBase; // Forward declare since no objects will be made of this

class Machine
{
public:
	Machine();
	virtual ~Machine();

	// Parses n number of lines in the gcode
	void parseGcode(int lineCount, int offset);
	void parseGcode(); // Creates commands for ALL gcode instruction

	double* getPosition();

	// Get / Set methods
	String getGcode();
	void setGcode(String arg_gcode);

private:
	// End stop pin, stepper pin, stepper type
	Axis xAxis = Axis(2, 3);
	Axis yAxis = Axis(7, 8);
	Axis zAxis = Axis(12, 13);

	String gcode;

	std::deque<CommandBase*> commands;

	String removeComments(String raw); // Removes comments from gcode
	int getArraySize(String array[]);
};

#endif /* MACHINE_H_ */
