#ifndef STEPMOTOROLD_H_
#define STEPMOTOROLD_H_

#include "Arduino.h"
#include <sstream>

#include "Global.h"
#include "thread/actions/Action.hpp"
#include "thread/actions/ActionStep.h"

class StepMotorOLD
{
public:
	StepMotorOLD(int stepType, int pin);
	virtual ~StepMotorOLD();

	void move(int steps, int time);
	void move(int steps);
	void step(int direction);

private:
	// How many steps / phases the motor supports
	const int STEP_TYPE;
	const int PIN;

	int phase = 0; // 0 thru STEP_TYPE

	// Returns "stepper-PIN" where PIN is the starting pin
	String getStepperId();
};

#endif /* STEPMOTOROLD_H_ */
