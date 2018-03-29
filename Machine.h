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

	double* getPosition();

	// Get / Set methods
	String getGcode();
	void setGcode(String arg_gcode);
	Axis* getAxis(char axisChar);
	double getFeedrate();
	void setFeedrate(double arg_feedrate);

private:
	// End stop pin, stepper pin
	Axis xAxis = Axis(Configuration::X_STEP_PIN, Configuration::X_DIR_PIN, Configuration::X_SWITCH);
	Axis yAxis = Axis(Configuration::Y_STEP_PIN, Configuration::Y_DIR_PIN, Configuration::Y_SWITCH);
	Axis zAxis = Axis(Configuration::Z_STEP_PIN, Configuration::Z_DIR_PIN, Configuration::Z_SWITCH);
	// Extruder:
	Axis eAxis = Axis(Configuration::E_STEP_PIN, Configuration::E_DIR_PIN, Configuration::E_SWITCH);
	double feedrate = Configuration::MAX_FEEDRATE; // unit/min

	String gcode;

	std::deque<CommandBase*> commands;

	String removeComments(String raw); // Removes comments from gcode
	int getArraySize(String array[]);
};

#endif /* MACHINE_H_ */
