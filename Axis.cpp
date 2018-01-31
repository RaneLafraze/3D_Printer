#include "Axis.h"


Axis::Axis(int arg_endStopPin, StepMotor* arg_axisMotor)
{
	axisMotor = arg_axisMotor;
	endStopPin = arg_endStopPin;

	pinMode(endStopPin, INPUT);
	// To change speed, change the initial value
	// of these variables since they are used here to
	// calculate the delay of milliseconds
	// between steps
	maxSpeedMM = round((maxSpeedMM * 1000) / Configuration::STEP_PER_MM);
	maxSpeedIN = round((maxSpeedIN * 1000) / Configuration::STEP_PER_IN);
}

Axis::Axis(int arg_endStopPin, int arg_stepperPin)
{
	axisMotor = new StepMotor(arg_stepperPin);
	endStopPin = arg_endStopPin;

	pinMode(endStopPin, INPUT);
	maxSpeedMM = round((maxSpeedMM * 1000) / Configuration::STEP_PER_MM);
	maxSpeedIN = round((maxSpeedIN * 1000) / Configuration::STEP_PER_IN);
}

/**
 * Moves this axis as fast as possible to the target
 * position.
 */
void Axis::moveAxis(double targetPos)
{
	if(units == Configuration::MM)
	{
		moveAxis(targetPos, maxSpeedMM);
	} else if(units == Configuration::IN)
	{
		moveAxis(targetPos, maxSpeedIN);
	}
}

/**
 * Moves the stepper motor associated with this axis
 * to the given position. Before calling this method,
 * the program needs to check to make sure the position
 * is valid and inside the build area. The second
 * speed parameter is the delay in milliseconds
 * that this move should take place over.
 */
void Axis::moveAxis(double targetPos, int speed)
{

	double movement = -1 * (position - targetPos);
	// * -1 to make the direction move correctly
	// Otherwise, the movement variable is inverted

	// A safety check should have been performed
	// before this method to ensure that
	// targetPos was within the boundaries
	// of the build dimensions
	if(units == Configuration::MM)
	{
		axisMotor->move(movement * Configuration::STEP_PER_MM, speed);
	} else if(units == Configuration::IN)
	{
		axisMotor->move(movement * Configuration::STEP_PER_IN, speed);
	}
	position = targetPos;

}

/**
 * This will evaluate the state of the end stop switch. If the
 * end stop switch is close (i.e. is on), then this method will return
 * true. Otherwise, it will return false.
 *
 * @return
 * True, if the end stop pin reads high. Otherwise false.
 */
bool Axis::readEndStopPin()
{
	if(digitalRead(endStopPin) == HIGH) {
		return true;
	} else
	{
		return false;
	}
}

// Get / Set methods

void Axis::setPosition(double newPosition)
{
	position = newPosition;
}
double Axis::getPosition()
{
	return position;
}

void Axis::setUnits(Configuration::unitEnum newUnit)
{
	units = newUnit;
}
Configuration::unitEnum Axis::getUnits()
{
	return units;
}


