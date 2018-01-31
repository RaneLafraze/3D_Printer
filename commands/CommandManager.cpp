#include "CommandManager.h"
#include "AllCommands.h"

CommandManager::CommandManager(Machine *arg_machine)
{
	machine = arg_machine;
}

CommandManager::~CommandManager()
{

}

/**
 * Add all possible commands to the deque here.
 */
void CommandManager::initCommands()
{

	registeredCommands.push_back(G1("G1", "G1", machine));

}

CommandBase* CommandManager::getCommandByName(String name)
{
	int index = indexOfName(name);

	if(index != -1)
	{
		return &registeredCommands.at(index);
	} else
	{
		return 0;
	}
}

CommandBase* CommandManager::getCommand(String tag)
{
	int index = indexOf(tag);

	if(index != -1)
	{
		return &registeredCommands.at(index);
	} else
	{
		return 0;
	}
}

CommandBase* CommandManager::getCommand(int index)
{
	return &registeredCommands.at(index);
}

int CommandManager::indexOfName(String name)
{
	CommandBase cmd;

	for(unsigned int s = 0; s < registeredCommands.size(); s++)
	{
		cmd = registeredCommands.at(s);
		if(cmd.getName().equalsIgnoreCase(name))
		{
			return s;
		}
	}
	return -1;
}

int CommandManager::indexOf(String tag)
{
	CommandBase cmd;

	for(unsigned int s = 0; s < registeredCommands.size(); s++)
	{
		cmd = registeredCommands.at(s);
		if(cmd.getTag().equalsIgnoreCase(tag))
		{
			return s;
		}
	}
	return -1;
}

/**
 * Compares both the tag and name to see if they are equal
 */
int CommandManager::indexOf(CommandBase *command)
{
	CommandBase cmd;

	for(unsigned int s = 0; s < registeredCommands.size(); s++)
	{
		cmd = registeredCommands.at(s);
		if(cmd.getName().equalsIgnoreCase(command->getName()))
		{
			// Nest so it's easier to read
			if(cmd.getTag().equalsIgnoreCase(command->getTag()))
			{
				return s;
			}
		}
	}
	return -1;
}
