#ifndef GLOBAL_H_
#define GLOBAL_H_

#include "Machine.h"
#include "commands/CommandManager.h"

//#include "Arduino.h"
//#include "Machine.h"
//#include "thread/ThreadManager.h"
//#include "commands/CommandManager.h"

class Machine;
class CommandManager;

// Will store global variables and objects
class Global {
public:
	Global();
	virtual ~Global();

	static Machine machine;
	static CommandManager cmdManager;

};

#endif /* GLOBAL_H_ */
