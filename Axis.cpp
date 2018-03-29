#include "Axis.h"


Axis::Axis(StepMotor* arg_axisMotor, int arg_endStopPin)
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

Axis::Axis(int arg_stepperPin, int arg_dirPin, int arg_endStopPin)
{
	axisMotor = new StepMotor(arg_stepperPin, arg_dirPin);
	endStopPin = arg_endStopPin;

	pinMode(endStopPin, INPUT);
	maxSpeedMM = round((maxSpeedMM * 1000) / Configuration::STEP_PER_MM);
	maxSpeedIN = round((maxSpeedIN * 1000) / Configuration::STEP_PER_IN);

}

Axis::~Axis()
{

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
 * @param usDelay
 * default = 0. The delay in microseconds after the step
 */
void Axis::moveOneStep(int direction, int usDelay)
{

	axisMotor->step(direction);
	if(usDelay > 16000) // Max delay for microseconds
	{
		delay(usDelay / 1000); // Delay milliseconds instead
	} else
	{
		delayMicroseconds(usDelay);
	}

	if(units == Configuration::MM)
	{
		// * direction to support positive or negative changes
		position = position + (Configuration::MM_PER_STEP * direction);
	} else if(units == Configuration::IN) {
		position = position + (Configuration::IN_PER_STEP * direction);
	}

//	Serial.print(endStopPin);
//	Serial.print(" position=");
//	Serial.println(position);
//	Serial.println();

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
	Serial.println("SET");
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


