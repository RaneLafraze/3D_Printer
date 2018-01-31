#include "StepMotorOLD.h"

/*
 * Object for a Stepper motor. The first parameter
 * specifies how many steps are in a cycle (3, or 4 step
 * motors). The second parameter, pin, specifies the
 * LOW starting pin. (i.e. pin = 4.
 * initialize pins 4, 5, 6, and 7 for output).
 */
StepMotorOLD::StepMotorOLD(int stepType, int pin)
		: STEP_TYPE(stepType), PIN(pin)
{

	// Set up the pins for output
	for (int p = PIN; p < (PIN + STEP_TYPE); p++)
	{
		pinMode(p, OUTPUT);
	}

}

StepMotorOLD::~StepMotorOLD()
{

}

/*
 * Move the stepper motor shaft the number of steps
 * in the given amount of time in milliseconds.
 * NOTE: The delay in milliseconds cannot be less
 * than the number of steps since the shaft
 * will not move if the delay between phase
 * changes is less than 1 millisecond
 */
void StepMotorOLD::move(int steps, int time)
{
	int direction = steps / abs(steps);
	int microPerStep = 0;

	if (direction == 0)
	{
		step(0); // Turn off all phases
		return; // Exit method
	}

	// Microseconds per every step (delay per step)
	microPerStep = round((time / steps) * 1000);

	// The motor won't move if the delay between
	// phase changes is less than 1 millisecond
	if (time > steps)
	{
		time = steps;
	}

	for (int s = 0; s < abs(steps); s++)
	{
		// Stepping
//		Action *step = new ActionStep("step", getStepperId(), this, direction);
//		Global::threadManager.addAction(step);

		// "Delay"
		Action *delay = new Action("delay", getStepperId(), 0, microPerStep);
		Global::threadManager.addAction(delay);
		// This isn't an actual delay, but it will take up an empty
		// chunk of time, acting like a delay

//		step(direction);
//		delayMicroseconds(microPerStep);
	}

}

/*
 * This will move the stepper motor shaft with the
 * given number of steps. NOTE: This method does
 * not have a built in delay, so it is not
 * recommenced to be used with large step values.
 * Instead, use  move(steps, time)
 */
void StepMotorOLD::move(int steps)
{
	int direction = steps / abs(steps);

	if (direction != 0)
	{
		for (int s = 0; s < abs(steps); s++)
		{
			step(direction);
		}
	} else
	{
		step(0);
	}
}

/*
 * Method that changes the phase of the stepper motor
 * depending on the integer given (-1, 0, 1). -1 will
 * increment the phase backward, 0 will turn all
 * coils / phases off, and 1 will increment the
 * phases forward. This method can be used in a
 * loop to turn the stepper motor shaft.
 */
void StepMotorOLD::step(int direction)
{
	// Make sure all stages are off to start with
	for (int p = 0; p < STEP_TYPE; p++)
	{
		digitalWrite(PIN + p, LOW);
	}

	// Adjust the phase based on direction
	if ((direction > 0) || (direction < 0))
	{
		digitalWrite(PIN + phase, HIGH);
		phase = phase + direction;
	}

	if (phase > STEP_TYPE)
	{
		phase = 0;
	} else if (phase < 0)
	{
		phase = STEP_TYPE;
	}

}

/**
 * Returns a formatted string, following this
 * convention: "stepper-PIN" where PIN is
 * the starting pin of this motor
 */
String StepMotorOLD::getStepperId()
{
	String id = "stepper-";
	id.concat(PIN);
	return id;
}
