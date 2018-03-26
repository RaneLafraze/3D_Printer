#ifndef CONFIGURATION_H_
#define CONFIGURATION_H_

#include "Arduino.h"


// Define ports / connections in this class
class Configuration
{
public:
	// millimeters or inches
	enum unitEnum {MM, IN};

	// constexpr info:
	// http://stackoverflow.com/questions/14116003/difference-between-constexpr-and-const
	static constexpr double MM_PER_STEP = 0.3; // mm. moved in 1 step
	static constexpr double IN_PER_STEP = 0.1; // in. moved in 1 step
	// TODO: \/ Remove these variables as they can be obtained from the ones above
	static constexpr double STEP_PER_MM = 3.0; // steps moved in 1 mm
	static constexpr double STEP_PER_IN = 10.0; // steps moved in 1 in

	static int MIN_STEPPER_DELAY = 300; // Min. delay in microseconds to turn

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
