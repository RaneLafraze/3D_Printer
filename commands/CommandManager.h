#ifndef COMMANDS_COMMANDMANAGER_H_
#define COMMANDS_COMMANDMANAGER_H_

#include "CommandBase.hpp"
#include "../Machine.h"

#include <deque>
#include "Arduino.h"

//#include "Arduino.h"
//#include "ArduinoSTL.h"
//#include <deque>
//
//#include "CommandBase.hpp"
//#include "AllCommands.h"
//#include "../Machine.h"


class CommandManager
{
public:
	CommandManager(Machine *arg_machine);
	virtual ~CommandManager();

	std::deque<CommandBase> registeredCommands;

	CommandBase* getCommandByName(String name);
	CommandBase* getCommand(String tag);
	CommandBase* getCommand(int index);

	int indexOfName(String name);
	int indexOf(String tag);
	int indexOf(CommandBase *command);

private:
	void initCommands(); // Adds all commands to the deque

	Machine *machine;

};

#endif /* COMMANDS_COMMANDMANAGER_H_ */
