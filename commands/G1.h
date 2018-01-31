#ifndef COMMANDS_G1_H_
#define COMMANDS_G1_H_

#include "CommandBase.hpp"
#include "../Machine.h"

#include "Arduino.h"

//#include "../Machine.h"

//class Machine;

class G1 : public CommandBase
{
public:
	G1(String arg_name, String arg_tag, Machine *arg_machine);
	G1(String arg_tag, Machine *arg_machine);
	virtual ~G1();

	void execute(String line); // Override from CommandBase
};

#endif /* COMMANDS_G1_H_ */
