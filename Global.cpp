#include "Global.h"

Global::Global() {
	machine = Machine();
	threadManager = ThreadManager();
	cmdManager = CommandManager(&machine);
}

Global::~Global() {

}

