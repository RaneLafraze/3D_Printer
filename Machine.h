#ifndef MACHINE_H_
#define MACHINE_H_

//#include "commands/CommandBase.hpp"
#include "Axis.h"
#include "Configuration.h"

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

	double getPosition(short axis);

	// Get / Set methods
	String getGcode();
	void setGcode(String arg_gcode);
	Axis* getAxis(char axisChar);
	double getFeedrate();
	void setFeedrate(double arg_feedrate);

private:
	// End stop pin, stepper pin
	Axis xAxis;;
	Axis yAxis;
	Axis zAxis;
	// Extruder:
	Axis eAxis;
	double feedrate = Configuration::MAX_FEEDRATE; // unit/min

	String gcode;

	std::deque<CommandBase*> commands;

	String removeComments(String raw); // Removes comments from gcode
	int getArraySize(String array[]);
};

#endif /* MACHINE_H_ */
