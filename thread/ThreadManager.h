#ifndef THREAD_THREADMANAGER_H_
#define THREAD_THREADMANAGER_H_

#include "actions/Action.hpp"

#include <deque>
#include "Arduino.h"
// Library: https://github.com/mike-matera/ArduinoSTL
// Library: https://github.com/maniacbug/StandardCplusplus


using namespace std;

class ThreadManager
{
public:
	ThreadManager();
	virtual ~ThreadManager();

	void runActions();
	void runActions(unsigned int count);

	void addAction(Action *newAction);

	Action* getFirstAction();
	Action* getLastAction();
private:
	deque<Action*> actions;

};

#endif /* THREAD_THREADMANAGER_H_ */
