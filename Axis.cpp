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

///**
// * Moves this axis as fast as possible to the target
// * position.
// */
//void Axis::moveAxis(double targetPos)
//{
//	if(units == Configuration::MM)
//	{
//		moveAxis(targetPos, maxSpeedMM);
//	} else if(units == Configuration::IN)
//	{
//		moveAxis(targetPos, maxSpeedIN);
//	}
//}

/**
 * Moves the stepper motor associated with this axis
 * to the given position. Before calling this method,
 * the program needs to check to make sure the position
 * is valid and inside the build area. The second
 * speed parameter is the delay in milliseconds
 * that this move should take place over.
 *
 * @param targetPos
 * the target position of this axis, in the selected units
 * @param speed
 * default = -1. If left default, the max speed of the axis will be used
 */
void Axis::moveAxis(double targetPos, int speed)
{

	double movement = -1 * (position - targetPos);
	// * -1 to make the direction move correctly
	// Otherwise, the movement variable is inverted

	// If speed was not assigned, assume the fastest travel speed
	if(speed == -1)
	{
		if(units == Configuration::MM)
		{
			speed = maxSpeedMM;
		} else if(units == Configuration::IN)
		{
			speed = maxSpeedIN;
		} else
		{
			speed = 1;
		}
	}

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
 * This will advance the axis one step in the given direction.
 * This function executes without a delay by default. However,
 * an integer can be passed representing a time in microseconds
 * to delay after the motor has moved.
 *
 * @param direction
 * the direction to step
 * @param delay
 * default = 0. The delay in microseconds after the step
 */
void Axis::moveOneStep(int direction, int delay)
{
	axisMotor->step(direction);
	delayMicroseconds(delay);

	if(units == Configuration::MM)
	{
		position = position + Configuration::MM_PER_STEP;
	} else if(units == Configuration::IN) {
		position = position + Configuration::IN_PER_STEP;
	}
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
	// End stops are enabled when low
	if(digitalRead(endStopPin) == LOW) {
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


