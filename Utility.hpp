#ifndef UTILITY_HPP_
#define UTILITY_HPP_

#include <math.h>

class Utility
{
public:
	Utility() {};
	virtual ~Utility() {};

	/**
	 * Rounds the given number to the place value provided.
	 * Examples:  (1.234, 100) --> 1.23
	 *            (465.4, 0.01) -> 5.00
	 *
	 * @param num
	 * the number to round
	 * @param place
	 * a multiple of 10, which will be multiplied by the number to
	 * achieve the desired rounding.
	 *
	 * @return
	 * The rounded number.
	 */
	static double roundToPlace(double num, int place)
	{
		return round(num * place) / place;
	}

	/**
	 * Method created to help fix problems with absolute value. It
	 * should also enable operations (+, -, ++) within the parameter.
	 *
	 * @param x
	 * a double, the value to be used in absolute value
	 *
	 * @return
	 * The number with the negative removed.
	 */
	static double absFixed(double x)
	{
		double num = x;
		return abs(num);
	}

};

#endif
