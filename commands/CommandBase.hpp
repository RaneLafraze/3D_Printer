#ifndef COMMANDS_COMMANDBASE_HPP_
#define COMMANDS_COMMANDBASE_HPP_

#include "../Machine.h"

#include "Arduino.h"

//class Machine;

/**
 * This class will be used as a template for all other
 * commands that can be found within g-code. A command
 * consists of the name of the command (optional) and
 * the tag (i.e. G1). Each command will have access
 * to the gentry systems and the line of text in the
 * g-code that corresponds to the tag (for parsing)
 */
class CommandBase
{
public:
	CommandBase() { }
	CommandBase(String arg_name, String arg_tag, Machine *arg_machine)
			: name(arg_name), tag(arg_tag), machine(arg_machine) { };
	CommandBase(String arg_tag, Machine *arg_machine)
			: name(arg_tag), tag(arg_tag), machine(arg_machine) { };
	// Name isn't given, so give it the tag value

	virtual ~CommandBase() { };
	//virtual void execute() = 0;

	// Where line is the line the command was found on (includes parameters)
	virtual void execute(String line) { };
	virtual void update(long delta) { }; // Should be called in a loop
	// ^ Have to be implemented to avoid vtable error


	// Get / Set methods
	String getName()
	{
		return name;
	}

	String getTag()
	{
		return tag;
	}

	bool getIsRunning()
	{
		return isRunning;
	}

protected:
	String name = ""; // Dummy values
	String tag = "";

	Machine *machine = 0;

	bool isRunning = false; // True after execute(), false once finished

};


#endif /* COMMANDS_COMMANDBASE_HPP_ */
