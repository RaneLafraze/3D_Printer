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

	void execute(String line) override; // Override from CommandBase
	void update(long delta) override;


private:
	Axis* getAxisByNum(int num);

	double startPos[4]; // 0->X, 1->Y, 2->Z, 3->E
	double targetPos[4];
	bool checkEndstop = false;

	double incrementDelays[4]; // In microseconds
	unsigned long startTime = 0.0;

};

#endif /* COMMANDS_G1_H_ */
