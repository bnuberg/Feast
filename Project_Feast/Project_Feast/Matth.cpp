#include "Matth.h"

/** Absolute Integer function, returns the absolute value of an integer.
*	@param value The input parameter, a positive or negative integer.
*	@return  The positive integral version of the input.
*/
int   Matth::absi(const int value)
{
	int neg = value * -1;
	return (value < 0) ? (neg) : value;
}

/** Absolute function, returns the floating point value of the input.
*	@param value The input parameter, a positive or negative float.
*	@return The positive version of the input parameter.
*/
float  Matth::abs(const float value)
{
	float neg = value * -1;
	return (value < 0) ? (neg) : value;
}

/** Inverse cosine function, returns the inverse cosine of the input in radians.
*	@param value The angle, in radians, to perform the operation on.
*	@return The floating point value of the inverse cosine of the input.
*/
float Matth::acos(const float value)
{
	return PI / 2.0f - Matth::asin(value);
}

/** Inverse sine function, returns the inverse sine of the input in radians.
*	@param value The angle, in radians, to perform the operation on.
*	@return The floating point value of the inverse sine of the input.
*/
float Matth::asin(const float value)
{
	float valueCubed = value * value * value;
	return value + (valueCubed / 6.0f) + (3.0f * valueCubed * value * value / 40.0f);
	// 6 = 2 * 3
	// 40 = 2 * 4 * 5
}

/** Inverse tangent function, returns the inverse tangent of the input in radians.
*	@param value The angle, in radians, to perform the operation on.
*	@return The floating point value of the inverse tangent of the input.
*/
float Matth::atan(const float value)
{
	float valueCubed = value * value * value;
	return value - (valueCubed / 3.0f) + (valueCubed * value * value / 5.0f);
}

/** The two-parameter version of the arctangent function. Will not divide by 0.
*	Returns 0 when the result would be infinite.
*	@param y The y coordinate
*	@param x The x coordinate
*	@return The angle in radians between the positive x-axis and the point (x, y)
*/
float Matth::atan2(const float y, const float x)
{
	if(x > 0)
	{
		return Matth::atan(y / x);
	}
	if(x < 0 && y >= 0)
	{
		return Matth::atan(y / x) + PI;
	}
	if(x < 0 && y < 0)
	{
		return Matth::atan(y / x) - PI;
	}
	if(x == 0 && y > 0)
	{
		return PI / 2.0;
	}
	if(x == 0 && y < 0)
	{
		return PI / -2.0;
	}
	return 0;
	// In this case the actual result would be infinite
}

/** Approximately function, returns true if the two values are approximately equal.
*	@param x The first value.
*	@param y The second value.
*	@return A boolean that is true if both values are equal when rounded.
*/
bool Matth::approximately(const float x, const float y)
{
	return (Matth::round(x) == Matth::round(y));
}

/** Average function, finds the average between two values.
*	@param x The first value.
*	@param y The second value.
*	@return The mean value of x and y.
*/
float Matth::average(const float x, const float y)
{
	return (x + y) / 2.0f;
}

/** Average function, finds the average between an int and a float.
*	@param x The first value.
*	@param y The second value.
*	@return The mean value of x and y.
*/
float Matth::average(const int x, const float y)
{
	return (x + y) / 2.0f;
}

/** Average function, finds the average between two integers.
*	@param x The first value.
*	@param y The second value.
*	@return The mean value of x and y.
*/
float Matth::average(const int x, const int y)
{
	return (x + y) / 2.0f;
}

/** Ceiling function, returns an integer of the input rounded up.
*	@param value The input value.
*	@return The rounded up version of the input as an int.
*/
int  Matth::ceili(const float value)
{
	return Matth::floori(value) + 1;
}

/** Ceiling function, returns a float of the input rounded up.
*	@param value The input value.
*	@return The rounded up version of the input as a float.
*/
float Matth::ceil(const float value)
{
	return Matth::floori(value) + 1.0f;
}

/** Clamping function, returns the clamped value of the input between a specified maximum and a specified minimum.
*	@param value The input value.
*	@param min The minimum value.
*	@param max The maximum value.
*	@return The clamped version of the input between min and max as an integer.
*/
int  Matth::clampi(const int value, const int min, const int max)
{
	if(value < min)
		return min;
	if(value > max)
		return max;
	return value;
}

/** Clamping function, returns the clamped value of the input between a specified maximum and a specified minimum.
*	@param value The input value.
*	@param min The minimum value.
*	@param max The maximum value.
*	@return The clamped version of the input between min and max as a float.
*/
float Matth::clamp(const float value, const float min, const float max)
{
	if(value < min)
		return min;
	if(value > max)
		return max;
	return value;
}

/** Clamping function, returns a floating point number clamped between 0 and 1.
*	@param value The value to be clamped.
*	@return The clamped value.
*/
float Matth::clamp01(const float value)
{
	return Matth::clamp(value, 0, 1);
}

// TODO
int Matth::closestPowerOfTwo(const float value)
{
	return 0;
}

// TODO
int Matth::closestPowerOfTwo(const int value)
{
	return 0;
}

/** Cosine function, returns the cosine of the input in radians.
*	@param value The angle in radians to be cosined.
*	@return The cosined value.
*/
float Matth::cos(const float value)
{
	float valueSquared = value * value;
	return 1.0f - (valueSquared / 2.0f) + (valueSquared * valueSquared / 24.0f);
	// 2 = 2!
	// 24 = 4!
}

/** Sine function, returns the sine of the input in radians.
*	@param value The angle in radians to be sined.
*	@return The sined value.
*/
float Matth::sin(const float value)
{
	// As always for a faster operation this is an approximation
	float valueCubed = value * value * value;
	return value - (valueCubed / 6.0f) + (valueCubed * value * value / 120.0f);
	// 6 = 3!
	// 120 = 5!
}

/** Tangent function, returns the tangent of the input in radians.
*	@param value The angle in radians to be tangented.
*	@return The tangented value.
*/
float Matth::tan(const float value)
{
	float valueCubed = value * value * value;
	return value + (valueCubed / 3.0f) + (2.0f * valueCubed * value * value / 15.0f);
	//15 = 1 * 3 * 5
}

/** Cotangent function, returns the ratio of the adjacent side of the input angle in radians to the opposite side.
*	(Of a right-angled triangle)
*	@param value The angle in radians to be used in the operation.
*	@return The result of the cotangent operation on the input.
*/
float Matth::cot(const float value)
{
	return (1.0f / value) - (value / 3.0f) - (value * value * value / 45.0f);
}

/** Secant function, returns the ratio of the adjacent side of the input angle in radians to the opposite side.
*	(Of a right-angled triangle)
*	@param value The angle in radians to be used in the operation.
*	@return The result of the secant operation on the input.
*/
float Matth::sec(const float value)
{
	float valueSquared = value * value;
	return 1.0f + (valueSquared / 2.0f) + (5.0f * valueSquared * valueSquared / 24.0f);
}

/** Cosecant function, returns the ratio of the adjacent side of the input angle in radians to the opposite side.
*	(Of a right-angled triangle)
*	@param value The angle in radians to be used in the operation.
*	@return The result of the cosecant operation on the input.
*/
float Matth::csc(const float value)
{
	// See: https://www.mathportal.org/formulas/pdf/taylor-series-formulas.pdf
	return (1.0f / value) + (value / 6.0f) + (7 * value * value * value / 360);
}

// TODO
float Matth::deltaAngle(const float current, const float target)
{
	return 0.0f;
}

/** Exponential function, returns the mathematical constant e to a given power, using a Taylor series.
*	@param power The power to raise e to.
*	@return The value of e raised to the power of the input.
*/
float Matth::exp(const float power)
{
	// I tried to reduce the number of operations as much as possible.
	// Another approximation may be required.
	float pow2 = power * power;
	float pow3 = pow2 * power;
	float pow4 = pow2 * pow2;
	float pow5 = pow3 * pow2;
	return 1.0f +
		   power +
		   (pow2 / 2.0f) +
		   (pow3 / 6.0f) +
		   (pow4 / 24.0f) +
		   (pow5 / 120.0f) +
		   (pow3 * pow3 / 720.0f) +
		   (pow3 * pow4 / 5040.0f) +
		   (pow4 * pow4 / 40320.0f) +
		   (pow4 * pow5 / 362880.0f) +
		   (pow5 * pow5 / 3628800.0f);
	// 2 = 2!
	// 6 = 3!
	//24 = 4!
}

/** Simple exponential function, returns e to the given power using the modulo method.
*	@param power The power to raise e to.
*	@return The value of e raised to the power of the input.
*/
float Matth::exps(const int power)
{
	return pows(EULER_E, power);
}

/** Floor function, returns the integral version of a floating point input rounded down.
*	@param value The value to be rounded down.
*	@return The rounded down version of the input.
*/
int  Matth::floori(const float value)
{
	return (int)Matth::floor(value);
}

/** Floor function, returns a floating point number rounded down.
*	@param value The value to be rounded down.
*	@return The value of the input rounded down.
*/
float Matth::floor(const float value)
{
	// Check this works, note tenTimes is an integer
	int tenTimes = value * 10;
	return tenTimes / 10;
}

/** Conversion function, converts a float from linear space to gamma space. Approximately.
*	@param value The value to be converted.
*	@return The converted value.
*/
float Matth::linearToGammaSpace(const float value)
{
	// Article about it: http://filmicworlds.com/blog/linear-space-lighting-i-e-gamma/
	return Matth::sqrt(value);// should really be pow 0.454545
}

/** Conversion function, converts a float from gamma space to linear space. Approximately.
*	@param value The value to be converted.
*	@return The converted value.
*/
float Matth::gammaToLinearSpace(const float value)
{
	return Matth::powm(value, 2);// should really be 2.2
}

/** Checking function, checks whether the input is a power of 2 and returns true if it is.
*	This function is the slower of the 2.
*	@param value The value to test.
*	@return A boolean that is true when the input is a power of 2.
*/
bool Matth::isPowerOfTwo(const int value)
{
	if(value < 0)
		return false;
	int temp = value;
	while(temp != 1)
	{
		if(temp % 2 != 0)
			return false;
		temp /= 2;
	}
	return true;
}

/** Checking function, checks whether the input is a power of 2 and returns true if it is.
*	This function is the faster of the 2.
*	@param value The value to test.
*	@return A boolean that is true when the input is a power of 2.
*/
bool Matth::isPowerOfTwoe(const int value)
{
	// Taken from: http://graphics.stanford.edu/~seander/bithacks.html
	return value && !(value & (value - 1));
}

/** Linear interpolation function, interpolates between two values at a point between them.
*	The point is clamped between the start and the end.
*	@param start The smaller of the two values to interpolate between.
*	@param end The larger of the two values to interpolate between.
*	@param value The point at which the function interpolates.
*	@return The interpolated value of the inputs at the specified point.
*/
float Matth::lerp(const float start, const float end, const float value)
{
	return start + Matth::clamp(value, start, end) * (end - start);
}

// TODO
float Matth::lerpAngle(const float start, const float end, const float value)
{
	return 0.0f;
}

/** Linear interpolation function, interpolates between two values at a point.
*	Does not clamp the value between the start and the end.
*	@param start The smaller of the two values to interpolate between.
*	@param end The larger of the two values to interpolate between.
*	@param value The point at which the function interpolates.
*	@return The interpolated value of the inputs at the specified point.
*/
float Matth::lerpUnclamped(const float start, const float end, const float value)
{
	return start + value * (end - start);
}

/** Linear interpolation function, performs Hermite interpolation between two values at a point.
*	Sometimes called smoothstep or inverse interpolation.
*	Result is undefined if end >= start.
*	@param start The first value to interpolate between.
*	@param end The second value to interpolate between.
*	@param value The point at which the values are interpolated.
*	@return The result of the interpolation between start and end at value.
*/
float Matth::inverseLerp(const float start, const float end, const float value)
{
	// See: https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/smoothstep.xhtml
	float f = Matth::clamp((value - start) / (end - start), 0.0f, 1.0f);
	return f * f * (3.0f - 2.0f * f);
}

/** Logarithm function, returns the logarithm of a specified integral value to a specified integral base.
*	If the base is not suuplied it will use 10 as a base.
*	@param value The value which the logarithm is performed on.
*	@param base The base of the logarithm used in the function.
*	@return The logarithm of value to the base base.
*/
float Matth::log(const int value, const int base)
{
	return Matth::ln(value) / Matth::ln(base);
}

/** Logarithm function, returns the logarithm of a specified integral value to a specified base.
*	If the base is not suuplied it will use 10 as a base.
*	@param value The value which the logarithm is performed on.
*	@param base The base of the logarithm used in the function.
*	@return The logarithm of value to the base base.
*/
float Matth::log(const int value, const float base)
{
	return Matth::ln(value) / Matth::ln(base);
}

/** Logarithm function, returns the logarithm of a specified value to a specified base.
*	If the base is not suuplied it will use 10 as a base.
*	@param value The value which the logarithm is performed on.
*	@param base The base of the logarithm used in the function.
*	@return The logarithm of value to the base base.
*/
float Matth::log(const float value, const float base)
{
	return Matth::ln(value) / Matth::ln(base);
}

/** Natural logarithm function, returns the natural logarithm of an integer.
*	@param value The value that the operation is performed on.
*	@return The natural logarithm of the input value.
*/
float Matth::ln(const int value)
{
	// Make sure second parameter is specified to prevent recurrsion
	return Matth::ln(value, 3);
}

/** Natural logarithm function, returns the natural logarithm of a value.
*	@param value The value that the operation is performed on.
*	@param prec The precision of the function (number of loops) the default value is 3.
*	@return The natural logarithm of the input value.
*/
float Matth::ln(const float value, int prec)
{
	float y = (value - 1) / (value + 1);
	//float y3 = y * y * y;
	//return 2 * (y + THIRD * y3 + FIFTH * y3 * y * y);

	float runningTotal = 0.0f;

	for (int i = 0; i < prec; i+=2)
	{
		runningTotal += (pows(y, i + 1) * 1 / (i + 1));
	}

	return 2 * runningTotal;
}


/** Comparison function, performs a logical exclusive-or operation on two given booleans.
*	@param a The first boolean.
*	@param b The second boolean.
*	@return This value is true if one and only one of the given booleans is true.
*/
bool Matth::logicalXOR(const bool a, const bool b)
{
	return (!a != !b);
}

/*

// Given 2 integers, returns the largest
int  Matth::maxi(const int x, const int y)
{
	return (x > y) ? x : y;
}

// Given 2 floats, returns the largest
float Matth::max(const float x, const float y)
{
	return (x > y) ? x : y;
}

// Given 2 integers, returns the smallest
int  Matth::mini(const int x, const int y)
{
	return (x < y) ? x : y;
}

// Given 2 floats, returns the smallest
float Matth::min(const float x, const float y)
{
	return (x < y) ? x : y;
}

*/

// TODO
float Matth::moveTowards(const float current, const float target, const float maxDelta)
{
	return 0.0f;
}

// TODO
float Matth::moveTowardsAngle(const float current, const float target, const float maxDelta)
{
	return 0.0f;
}

/** Search function, finds the closest power of two larger than the given value.
*	Takes an integral number.
*	@param value The input smaller than the next power of two.
*	@return The next power of two.
*/
int Matth::nextPowerOfTwo(const int value)
{
	// See: https://www.hackerearth.com/practice/notes/round-a-number-to-the-next-power-of-2/
	int  returnValue  =  1 ;
	
	while  ( returnValue  <=  value)
	{
		returnValue  =  returnValue  <<  1 ;
	}
	return  returnValue ;
}

/** Search function, finds the closest power of two larger than the given value.
*	Takes a floating point number.
*	@param value The input smaller than the next power of two.
*	@return The next power of two.
*/
int Matth::nextPowerOfTwo(const float value)
{
	return Matth::nextPowerOfTwo((int)value);
}

/** Search function, finds the closest power of two larger than the given value.
*	Takes a floating point number.
*	Is faster than the other nextPowerOfTwo functions.
*	@param value The input smaller than the next power of two.
*	@return The next power of two.
*/
int Matth::nextPowerOfTwoe(const float value)
{
	// Again from: http://graphics.stanford.edu/~seander/bithacks.html
	unsigned int v = (int)value;
	v--;
	v |= v >> 1;
	v |= v >> 2;
	v |= v >> 4;
	v |= v >> 8;
	v |= v >> 16;
	v++;
	return v;
}

// TODO
float Matth::perlinNoise(const float x, const float y)
{
	return 0.0f;
}

// TODO
float Matth::pingPong(const float value, const float length)
{
	return 0.0f;
}

/** Power function, returns the power of an integer to another.
*	@param x The base.
*	@param y The power.
*	@return The value of x to the power y.
*/
int  Matth::powi(const int x, const int y)
{
	return (int)Matth::pow((float)x, (float)y);
}

/** Power function, returns the power of a float to an integer.
*	@param x The float base.
*	@param y The int power.
*	@return The value of x to the power y.
*/
float Matth::pow(const float x, const int y)
{
	return Matth::powm(x, (float)y);
}

/** Power function, returns the power of a float to another.
*	Uses exponential and natural log functions with a precision of 5 iterations.
*	@param x The base.
*	@param y The power.
*	@return The value of x to the power y.
*/
float Matth::powf(const float x, const float y)
{
	return Matth::exp(y * Matth::ln(x, 5));
}

/** Power function, returns the power of a float to another (truncated).
*	The human-logical way of finding the power of a number.
*	@param x The base.
*	@param y The power.
*	@return The value of x to the power y.
*/
float Matth::pows(const float x, const float y)
{
	if (y == 0)
		return 1.0f;
	if (x == 0)
		return 0.0f;

	int z = (int)y;

	float runningTotal = 1.0f;
	for (int i = 0; i < z; i++)
	{
		runningTotal *= x;
	}
	return runningTotal;
}

/** Power function, returns the power of an int to another.
*	Uses the modulo method.
*	@param x The base.
*	@param y The power.
*	@return The value of x to the power y.
*/
float Matth::powm(int x, int y)
{
	if(y == 0)
		return 1.0f;
	if(x == 0)
		return 0.0f;
	
	int result = 1;
	while(y > 0)
	{
		if(y & 1)
		{
			result = (result * x) % MOD;
		}
		
		x = (x * x) % MOD;
		y >>= 1;
	}
	return (float)result;
}

// TODO
float Matth::repeat(const float value, const float length)
{
	return 0.0f;
}

/** Rounding function, returns the value of the input rounded to the nearest integer.
*	Returns an int.
*	@param value The input to be rounded.
*	@return The value of the input correctly rounded.
*/
int  Matth::roundi(const float value)
{
	return (int)Matth::round(value);
}

/** Rounding function, returns the value of the input rounded to the nearest integer.
*	Returns a float.
*	@param value The input to be rounded.
*	@return The value of the input correctly rounded.
*/
float Matth::round(const float value)
{
	int intValue = (int)value;
	float tenths = value - intValue;
	if(10 * tenths > 4)// I.e. Greater than or equal to 5
		return Matth::ceil(value);
	return intValue;
}

/** Checking function, checks the sign of the input.
*	Takes an int.
*	@param value The value to check the sign of.
*	@return Returns -1 if the value is negative, 1 if it is positive.
*/
int Matth::sign(const int value)
{
	return (value < 0) ? -1 : 1;
}

/** Checking function, checks the sign of the input.
*	Takes a float.
*	@param value The value to check the sign of.
*	@return Returns -1 if the value is negative, 1 if it is positive.
*/
int Matth::sign(const float value)
{
	return (value < 0) ? -1 : 1;
}

/** Checking function, checks whether the input is positive or not.
*	Takes an int.
*	@param value The value to check the positivity of.
*	@return Returns true if the value is positive (value > 0).
*/
bool Matth::isPositive(const int value)
{
	return value > 0;
}

/** Checking function, checks whether the input is positive or not.
*	Takes a float.
*	@param value The value to check the positivity of.
*	@return Returns true if the value is positive (value > 0).
*/
bool Matth::isPositive(const float value)
{
	return value > 0;
}

/** Checking function, checks whether the input is negative or not.
*	Takes an int.
*	@param value The value to check the negativity of.
*	@return Returns true if the value is negative (value < 0).
*/
bool Matth::isNegative(const int value)
{
	return value < 0;
}

/** Checking function, checks whether the input is negative or not.
*	Takes a float.
*	@param value The value to check the negativity of.
*	@return Returns true if the value is negative (value < 0).
*/
bool Matth::isNegative(const float value)
{
	return value < 0;
}

// Skipping a few recommended functions, if we really need them you can add them later
/*
	smoothDamp
	smoothDampAngle
	smoothStep
*/

/** Square root function, finds the square root of the input.
*	Takes an int, returns an int.
*	@param value The value to square root.
*	@return The value of the input square rooted.
*/
int  Matth::sqrti(const int value)
{
	return (int)Matth::FIISRBOQ3C(value);
}

/** Square root function, finds the square root of the input.
*	Takes an int, returns a float.
*	@param value The value to square root.
*	@return The value of the input square rooted.
*/
float Matth::sqrt(const int value)
{
	return Matth::FIISRBOQ3C(value);
}


/** Square root function, uses the Newtonian method to find the square root of a number.
*	Developed by myself at age 15, converted from VB to C++ in 2017.
*	Takes a float, returns a float.
*	@param value The value to square root.
*	@param prec The precision (number of iterations) of the function, it is 7 by default.
*	@return The value of the square root of the input.
*/
float Matth::sqrt(const float value, int prec)
{
	float r = 2.0f;
	float c = 0.0f;
	int i = 1;
	
	while(c != r && i != prec)
	{
		c = value / r;
		r = HALF * (r + c);
		i++;
	}
	return r;
}

/** Square root function, fast inverse inverse square root based on quake 3 code (with original comments).
*	This is probably the fastest of the square roots in this library.
*	Takes a float, returns a float.
*	@param value The value to square root.
*	@return The value of the square root of the input.
*/
float Matth::FIISRBOQ3C(const float value)
{
	long i;
	float x2, y;
	
	x2 = value * HALF;
	y = value;
	i = * (long *) &y; 								// evil floating point bit level hacking
	i = 0x5f3759df - (i >> 1);						// what the fuck?
	y = * (float *) &i;
	y = y * (THREE_HALF - (x2 * y * y)); 			// 1st iteration
	//	y  = y * ( THREE_HALF - ( x2 * y * y ) );   // 2nd iteration, this can be removed
	
	return 1.0f / y;
}

/** Square root function, uses the natural logarithm and exponential to find an approximation for the
*	square root of a number.
*	Probably slow due it using the exponential function and logarithm function at precision 100.
*	Takes a float, returns a float.
*	@param value The value to square root.
*	@return The value of the square root of the input.
*/
float Matth::sqrtWithNaturalLog(const float value)
{
	// log(x^0.5) = 0.5 * log(x)
	float logNum = Matth::ln(value, 100);
	float halfLogNum = logNum / 2.0f;
	return Matth::exp(halfLogNum);
}
