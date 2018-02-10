#include "Global.h"

Global::Global() {
	machine = Machine();
	cmdManager = CommandManager(&machine);
}

Global::~Global() {

}

