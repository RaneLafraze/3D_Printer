#ifndef CONFIGURATION_H_
#define CONFIGURATION_H_

#include "Arduino.h"


// Define ports / connections in this class
class Configuration
{
public:
	// millimeters or inches
	enum unitEnum {MM, IN};

	// Pin assignments
	// --X--
	static const int X_STEP_PIN = 3;
	static const int X_DIR_PIN = 4;
	static const int X_SWITCH = 5; // Endstop pin

	// --Y--
	static const int Y_STEP_PIN = 6;
	static const int Y_DIR_PIN = 7;
	static const int Y_SWITCH = 8;

	// --Z--
	static const int Z_STEP_PIN = 9;
	static const int Z_DIR_PIN = 10;
	static const int Z_SWITCH = 11;

	// --Extruder--
	static const int E_STEP_PIN = 12;
	static const int E_DIR_PIN = 13;
	static const int E_SWITCH = 0; // Filament detector

	// Useful formulas:    delay(ms) = 1000ms / (mm * steps)
	// NEMA steps=200      mm = 1000ms / (delay(ms) * steps)

	// With minimum delay of 300 microseconds (600 total)
	// Max speed = 8.3 mm/s   0.327 in/s

	// constexpr info:
	// http://stackoverflow.com/questions/14116003/difference-between-constexpr-and-const
	static constexpr double MM_PER_STEP = 0.005; // mm. moved in 1 step
	static constexpr double IN_PER_STEP = 0.000197; // in. moved in 1 step
	// TODO: \/ Remove these variables as they can be obtained from the ones above
	static constexpr double STEP_PER_MM = 200.0; // steps moved in 1 mm
	static constexpr double STEP_PER_IN = 5080.0; // steps moved in 1 in
	static constexpr double PRECISION = 1000.0; // Maximum accuracy

	static constexpr int MIN_STEPPER_DELAY = 300; // Min. delay in microseconds to turn
	static constexpr int MAX_FEEDRATE = 500; // 8.3mm/s * 60

	// Is (0, 0) in the center of the build plate?
	// If not, it is in the corner
	static const bool BUILD_CENTERED = false;
	static const int BUILD_WIDTH_MM = 400;
	static const int BUILD_LENGTH_MM = 400;
	static const int BUILD_HEIGHT_MM = 400;
	static const int BUILD_WIDTH_IN = 200;
	static const int BUILD_LENGTH_IN = 200;
	static const int BUILD_HEIGHT_IN = 200;

};


#endif /* CONFIGURATION_H_ */
