#include "StepMotor.h"

#include "Global.h"
#include "Configuration.h"

/**
 * Used as the base object for the machine. It is a Stepper Motor
 * object constructed around the A4988 Driver. The integer provided
 * corresponds to the pin that will control the stepping of the motor.
 *
 * @param arg_stepPin
 * the pin for the step control
 * @param arg_dirPin
 * the pin to control direction
 */
StepMotor::StepMotor(int arg_stepPin, int arg_dirPin) : STEP_PIN(arg_stepPin), DIR_PIN(arg_dirPin)
{	
	
	pinMode(STEP_PIN, OUTPUT); // Step control
	pinMode(DIR_PIN, OUTPUT); // Direction

}

StepMotor::~StepMotor()
{

}

/**
 * Move the stepper motor shaft the number of steps
 * in the given amount of time in milliseconds.
 * NOTE: The delay in milliseconds cannot be less
 * than the number of steps since the shaft
 * will not move if the delay between phase
 * changes is less than 1 millisecond.
 *
 * @param steps
 * the number of steps for the given motor to take
 * @param time
 * the amount of time to step
 */
//void StepMotor::move(int steps, int time)
//{
//
//	int direction = steps / abs(steps);
//	int microPerStep = 0;
//
//	// Do nothing if steps is 0
//	if((steps == 0) || (direction == 0))
//	{
//		return;
//	}
//
//	// Microseconds per every step (delay per step)
//	microPerStep = round((time / steps) * 1000);
//
//	// The motor won't move if the delay between
//	// phase changes is less than 1 microsecond
//	if (time > steps)
//	{
//		time = steps;
//	}
//
//	for (int s = 0; s < abs(steps); s++)
//	{
//		// Stepping
//		Action *step = new ActionStep("step", getStepperId(), this, direction);
//		Global::threadManager.addAction(step);
//
//		// "Delay"
//		Action *delay = new Action("delay", getStepperId(), 0, microPerStep);
//		Global::threadManager.addAction(delay);
//		// This isn't an actual delay, but it will take up an empty
//		// chunk of time, acting like a delay
//
//	}
//}

/*
 * This will move the stepper motor shaft with the
 * given number of steps. NOTE: By default, this method
 * does not have a built in delay. It is HIGHLY recommended
 * that a integer greater than 300 is passed in to the second
 * parameter.
 *
 * @param steps
 * the number of steps to move
 * @param time
 * default = -1. Delay in microseconds, should be greater than 300.
 * If left at -1, it will be set to the fastest step speed (lowest
 * delay)
 */
void StepMotor::move(int steps, int time)
{
	int direction = steps / abs(steps);

	if(time == -1)
	{
		time = Configuration::MIN_STEPPER_DELAY;
	}

	if (direction != 0)
	{
		for (int s = 0; s < abs(steps); s++)
		{
			step(direction);
			delayMicroseconds(time);
		}
	}
}

/**
 * Method that steps or advances the stepper motor in the given direction.
 * If direction equals one, the stepper motor will move clockwise. If
 * it equals negative one, the stepper motor will move counter-clockwise.
 * Any other value will cause the method to exit as it's an invalid input.
 *
 * @param direction
 * the direction the shaft of the motor will turn
 */
void StepMotor::step(int direction)
{

	pulse(direction);
	delayMicroseconds(Configuration::MIN_STEPPER_DELAY);
	pulse(direction);

//	// TODO: Make sure these direction values are correct
//	if(direction == 1)
//	{
//		digitalWrite(DIR_PIN, HIGH);
//	} else if(direction == -1)
//	{
//		digitalWrite(DIR_PIN, LOW);
//	} else
//	{
//		// direction is invalid, so exit
//		return;
//	}
//
//	digitalWrite(STEP_PIN, HIGH);
//	delayMicroseconds(Configuration::MIN_STEPPER_DELAY); // Fastest delay for Arduino
//	digitalWrite(STEP_PIN, LOW);

}

/**
 * Will pulse the step pin to achieve movement in the motor. The
 * integer parameter determines the direction of the motor. A positive
 * 1 will turn clockwise, whereas a negative one will turn counter-clockwise.
 * This has no built in delay in order to achieve synchronous operations.
 * It will return true when the shaft is unpowered (STEP_PIN is LOW)
 *
 * @param direction
 * direction of the shaft; positive -> clockwise, negative -> counter
 *
 * @return
 * True, when the STEP pin has written a value of LOW. Any other time,
 * false will be returned.
 */
bool StepMotor::pulse(int direction)
{

	// TODO: Make sure these direction values are correct
	if(direction >= 1)
	{
		digitalWrite(DIR_PIN, HIGH);
	} else if(direction <= -1)
	{
		digitalWrite(DIR_PIN, LOW);
	} else
	{
		// direction is invalid, so exit
		return false;
	}

	if(isHigh)
	{
		digitalWrite(STEP_PIN, LOW);
		isHigh = false;
		return true; // To signify the end of a step
	} else {
		digitalWrite(STEP_PIN, HIGH);
		isHigh = true;
		return false; // This will have moved the motor, but needs to be ended
	}

//	digitalWrite(STEP_PIN, HIGH);
//	delayMicroseconds(Configuration::MIN_STEPPER_DELAY); // Fastest delay for Arduino
//	digitalWrite(STEP_PIN, LOW);

}

/**
 * Returns a formatted string, following this
 * convention: "stepper-PIN" where PIN is
 * the starting pin of this motor.
 *
 * @return
 * A string with the stepper's pin number.
 */
String StepMotor::getStepperId()
{
	String id = "stepper-";
	id.concat(STEP_PIN);
	return id;
}

