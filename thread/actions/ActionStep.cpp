#include "ActionStep.h"

ActionStep::ActionStep(String arg_name, String arg_threadName, StepMotor *arg_stepper, int arg_direction)
	: Action(arg_name, arg_threadName, 0, 10)
{
	// This block may not be needed...
	name = arg_name;
	threadName = arg_threadName;
	startTime = 0; // Dummy value
	duration = 10;

	stepper = arg_stepper;
	direction = arg_direction;
}

ActionStep::~ActionStep()
{

}

void ActionStep::execute()
{
	stepper->step(direction);
}
