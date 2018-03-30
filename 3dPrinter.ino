#include "Machine.h"
#include "commands/AllCommands.h"
#include "Global.h"

#include "Arduino.h"

/* MEMORY LOG
 * 3/29/18  -  Able to run program with 7293 bytes of SRAM free
 *             13,344 bytes of flash
 *
 */

void checkMem();
int freeMemory();

// Variables
Machine machine = Machine();
G1 g1Command = G1("G1", "G1", &machine);


void setup()
{

	Serial.begin(9600);
	Serial.println("Machine initialized! Awaiting command...");
}

void loop()
{
	String input = "";

	// When the command isn't running, get the input
	if(!g1Command.getIsRunning())
	{
		input = "";
		//Serial.println("Ready for input...");

		while(Serial.available() > 0)
		{
			// Add the character to the string
			//input = input.concat(Serial.read());
			input = Serial.readString();
		}
		if(input.length() > 0)
		{
			Serial.print(F("Received input: "));
			Serial.println(input);

			Serial.println(F("Executing input as command...\n"));
			g1Command.execute(input);
		}

	} else
	{
		g1Command.update(0.0);
	}

#if defined(ARDUINO_AVR_MEGA2560)
	checkMem();
#endif
	//delay(1); // For stability(may not be needed)
}

void checkMem()
{
	// If using the Mega, check for less than 5k
	// IF using Uno, check for less than 500
#if defined(ARDUINO_AVR_MEGA2560)
	if(freeMemory() < 5000)
#else
	if(freeMemory() < 500)
#endif
	{
		Serial.println("Low SRAM!!");
	}
}

#ifdef __arm__
// should use uinstd.h to define sbrk but Due causes a conflict
extern "C" char* sbrk(int incr);
#else  // __ARM__
extern char *__brkval;
#endif  // __arm__

int freeMemory() {
  char top;
#ifdef __arm__
  return &top - reinterpret_cast<char*>(sbrk(0));
#elif defined(CORE_TEENSY) || (ARDUINO > 103 && ARDUINO != 151)
  return &top - __brkval;
#else  // __arm__
  return __brkval ? &top - __brkval : &top - __malloc_heap_start;
#endif  // __arm__
}
