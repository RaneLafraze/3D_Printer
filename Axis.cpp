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

	lastPulse = micros();

}

Axis::~Axis()
{

}

/**
 * Should be called in a loop to allow the axis to correctly
 * move the motor. This is needed in order for the motors to
 * move smoothly simultaneously.
 *
 * @param delta
 * time since last update was called (?? may remove ??)
 */
void Axis::update(long delta)
{

	// Worried about overflowing? Sleep easy my friend: https://bit.ly/2L29SFK
	elapsedTime = elapsedTime + delta;

	// If our current position is not our target position, move
	if(position != targetPos)
	{
//		// Multiply to avoid arithmetic errors
//		position = position * Configuration::PRECISION;
//		targetPos = targetPos * Configuration::PRECISION;

		int direction = 0;
		// TODO: Make sure these direction variables are right
		if(position > targetPos)
		{
			direction = -1;
		} else if(position < targetPos) {
			direction = 1;
		}

		double stepAdvance = 0.0;
		if(units == Configuration::MM)
		{
			// * direction to support positive or negative changes
			stepAdvance = (Configuration::MM_PER_STEP * direction * Configuration::PRECISION);
		} else if(units == Configuration::IN) {
			stepAdvance = (Configuration::IN_PER_STEP * direction * Configuration::PRECISION);
		}

		// If the next step can occur, do it!
		if(elapsedTime - lastPulse >= nextWait)
		{
			if(axisMotor->pulse(direction)) // If motor moved, update position
			{
				// Multiply to avoid arithmetic errors
				position = position * Configuration::PRECISION;
				position = position + stepAdvance;
				position = position / Configuration::PRECISION;
				// Convert back to readable double

				nextWait = stepInterval;
			} else
			{
				nextWait = Configuration::MIN_STEPPER_DELAY;
				// Since we don't want the step interval between
				// the high->low pulse of motor, only between
				// steps. i.e. a stepInterval of 1 second should only
				// effect the step time and not be doubled by high->low pulse
			}
			lastPulse = elapsedTime;
		}

//		// Convert back to readable double
//		position = position / Configuration::PRECISION;
//		targetPos = targetPos / Configuration::PRECISION;
	} // End of movement if

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

	this->targetPos = targetPos;
	if(speed == -1)
	{
		speed = Configuration::MIN_STEPPER_DELAY;
	}
	this->stepInterval = speed;

//	double movement = -1 * (position - targetPos);
//	// * -1 to make the direction move correctly
//	// Otherwise, the movement variable is inverted
//
//	// If speed was not assigned, assume the fastest travel speed
//	if(speed == -1)
//	{
//		if(units == Configuration::MM)
//		{
//			speed = maxSpeedMM;
//		} else if(units == Configuration::IN)
//		{
//			speed = maxSpeedIN;
//		} else
//		{
//			speed = 1;
//		}
//	}
//
//	// A safety check should have been performed
//	// before this method to ensure that
//	// targetPos was within the boundaries
//	// of the build dimensions
//	if(units == Configuration::MM)
//	{
//		axisMotor->move(movement * Configuration::STEP_PER_MM, speed);
//	} else if(units == Configuration::IN)
//	{
//		axisMotor->move(movement * Configuration::STEP_PER_IN, speed);
//	}
//	position = targetPos;

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

	// Kind of cheating... Maybe refactor and rename if this works
	targetPos = targetPos * Configuration::PRECISION;
	if(units == Configuration::MM)
	{
		targetPos = targetPos + (Configuration::MM_PER_STEP * direction * Configuration::PRECISION);
	} else if(units == Configuration::IN)
	{
		targetPos = targetPos + (Configuration::IN_PER_STEP * direction * Configuration::PRECISION);
	}
	targetPos = targetPos / 1000;

//	axisMotor->step(direction);
////	if(usDelay > 2000) // Max delay for microseconds
////	{
////		delay(usDelay / 1000); // Delay milliseconds instead
////	} else
////	{
////		delayMicroseconds(usDelay);
////	}
//
//	// Multiply to avoid arithmetic errors
//	position = position * Configuration::PRECISION;
//	if(units == Configuration::MM)
//	{
//		// * direction to support positive or negative changes
//		position = position + (Configuration::MM_PER_STEP * direction * Configuration::PRECISION);
//	} else if(units == Configuration::IN) {
//		position = position + (Configuration::IN_PER_STEP * direction * Configuration::PRECISION);
//	}
//	// And convert back to double number
//	position = position / Configuration::PRECISION;

//	Serial.print(F("axis="));
//	Serial.println(endStopPin);

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

bool Axis::getIsIdle()
{
	return isIdle;
}

void Axis::setUnits(Configuration::unitEnum newUnit)
{
	units = newUnit;
}
Configuration::unitEnum Axis::getUnits()
{
	return units;
}


