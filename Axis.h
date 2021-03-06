#ifndef AXIS_H_
#define AXIS_H_

#include "StepMotor.h"
#include "Configuration.h"

#include "Arduino.h"

//class StepMotor;

class Axis
{
public:

	Axis(int arg_endStopPin, StepMotor* arg_axisMotor);
	Axis(int arg_endStopPin, int arg_stepperPin);
	virtual ~Axis();

	void moveAxis(double targetPos);
	void moveAxis(double targetPos, int speed);

	bool readEndStopPin();

	// Get / Set positions

	double getPosition();
	void setPosition(double newPosition);

	void setUnits(Configuration::unitEnum newUnit);
	Configuration::unitEnum getUnits();

private:
	StepMotor* axisMotor;

	int endStopPin = 0; // Pin for the end-stop for this axis
	double position = 0.0; // Position (either in mm. or in.)

	Configuration::unitEnum units = Configuration::MM;

	// Operations are in: Axis.cpp
	// Use the variable for steps for reaching a unit
	// of one. Then, divide this
	// by the number of millisecond delay wanted for
	// this movement to get the delay in milliseconds
	// per each step. This assumed that MM_PER_STEP
	// and IN_PER_STEP < 0
	//  Change this number \/ for mm (or in) per second
	int maxSpeedMM = 5; // 5 mm per second
	int maxSpeedIN = 2;
	// Not constant because these may need to be
	// changed while Arduino is running
	// Could also use   (1 / MM_PER_STEP) instead of
	// STEP_PER_MM

	// mm per step  and   in per step    are stored
	// within Configuration.h   To access, use
	// Configuration::MM_PER_STEP

};

#endif /* AXIS_H_ */
