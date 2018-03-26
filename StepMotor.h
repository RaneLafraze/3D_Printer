#ifndef STEPMOTOR_H_
#define STEPMOTOR_H_

#include "Arduino.h"


class StepMotor
{
public:
	StepMotor(int arg_pin);
	virtual ~StepMotor();

	void move(int steps, int time = -1);
	//void move(int steps);
	void step(int direction);

private:

	const int PIN;

	// Returns "stepper-PIN" where PIN is the starting pin
	String getStepperId();
};

#endif
