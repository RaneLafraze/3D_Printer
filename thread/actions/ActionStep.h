#ifndef THREAD_ACTIONS_ACTIONSTEP_H_
#define THREAD_ACTIONS_ACTIONSTEP_H_

#include "Action.hpp"
#include "../../StepMotor.h"

#include "Arduino.h"

//class StepMotor;

class ActionStep : public Action
{
public:
	ActionStep(String arg_name, String arg_threadName, StepMotor *arg_stepper, int arg_direction);
	virtual ~ActionStep();

	void execute();

private:
	StepMotor *stepper;
	int direction;

};

#endif /* THREAD_ACTIONS_ACTIONSTEP_H_ */
