#ifndef THREAD_ACTIONS_HPP_
#define THREAD_ACTIONS_HPP_

#include "Arduino.h"

// Make this like an interface
class Action
{
public:

	Action(String arg_name, String arg_threadName, int arg_startTime, int arg_duration)
		: name(arg_name), threadName(arg_threadName), startTime(arg_startTime), duration(arg_duration) { }
	virtual ~Action();
	// Expect this method to be overwritten by extension
	virtual void execute() { }

	// Get / Set methods

	void setName(String arg_name)
	{
		name = arg_name;
	}
	String getName()
	{
		return name;
	}

	void setThreadName(String arg_threadName)
	{
		threadName = arg_threadName;
	}
	String getThreadName()
	{
		return threadName;
	}

	void setStartTime(int arg_startTime)
	{
		startTime = arg_startTime;
	}
	int getStartTime()
	{
		return startTime;
	}

	void setDuration(int arg_duration)
	{
		duration = arg_duration;
	}
	int getDuration()
	{
		return duration;
	}

protected:
	String name;
	String threadName;

	int startTime; // Start time of this action MICROseconds
	int duration; // Time it takes for this action in MICROseconds

};

#endif /* THREAD_ACTION2_HPP_ */
