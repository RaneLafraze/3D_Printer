#ifndef STEPMOTOR_H_
#define STEPMOTOR_H_

#include "Arduino.h"


class StepMotor
{
public:
	StepMotor(int arg_stepPin, int arg_dirPin = -1);
	virtual ~StepMotor();

	void move(int steps, int time = -1);
	//void move(int steps);
	void step(int direction);
	bool pulse(int direction);

	// Returns "stepper-PIN" where PIN is the starting pin
	String getStepperId();

private:

	const int STEP_PIN;
	const int DIR_PIN;

	bool isHigh = false; // Is the STEP pin high?

};

#endif
