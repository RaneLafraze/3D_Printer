#include "ThreadManager.h"

ThreadManager::ThreadManager()
{

}

ThreadManager::~ThreadManager()
{

}

/*
 * Function that goes through all of
 * actions within the action deque, with
 * delays.
 */
void ThreadManager::runActions()
{
	runActions(actions.size());
}

/*
 * Function that runs n actions in the
 * 'actions' deque. n is the integer
 * passed in the parameter.
 */
void ThreadManager::runActions(unsigned int count)
{
	int microOffset = micros(); // Get current time

	count = count > actions.size() ? actions.size() : count;
	// x = (condition) ? (value_if_true) : (value_if_false);

	for(unsigned int r = 0; r < count; r++)
	{
		if(micros() >= (unsigned) actions.front()->getStartTime() + microOffset)
		{
			actions.front()->execute();
			actions.pop_front();
		} else {
			delayMicroseconds(1);
		}
	}
}

/*
 * This method will add the given action
 * to the action vector (or the "stack"
 * of processes. It will determine the start
 * time of the action based on previous
 * actions (of the same thread) and their
 * duration. This is the ideal way to add
 * actions and functions to the vector list.
 */
void ThreadManager::addAction(Action *newAction)
{
	String actionThread = ""; // Name of the thread of the new action
	int currentTime = 0; // Used to set the start time of the added action
	Action* latestAction = 0; // Most recent added action within the thread
	// /\ Must be a pointer. Objects cannot be 0 or null, but pointers can


	actionThread = newAction->getThreadName();

	// Start from the end of the list to find the "oldest" or most delayed
	// actions in the list.
	// Since 0 is an index, we have to "size - 1" and use >=
	for(int s = actions.size() - 1; s >= 0; s--)
	{
		if(actions.at(s)->getThreadName() == actionThread)
		{
			latestAction = actions.at(s);
			currentTime = latestAction->getStartTime() + latestAction->getDuration();
			s = -1; // End the loop
			break; // Exit loop
		}
	}

	// If no other action of the same thread was found:
	if(latestAction == 0)
	{
		currentTime = 0;
	}

	newAction->setStartTime(currentTime);
	actions.push_back(newAction);

}

Action* ThreadManager::getFirstAction()
{
	return actions.at(0);
}

Action* ThreadManager::getLastAction()
{
	return actions.at(actions.size());
}
