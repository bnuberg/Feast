#include "Matth.h"

/*
	Big 'ol warning:
	I have not compiled this code yet.
	I haven't run it either.
	It should work but it might not.
	Who knows?
	Ask me later.
	
	It compiles.

	Note that most of these are approximations
	for speed during runtime.

	Mostly accurate to 4 decimal places.
	Guarranteed to be accurate to 1 significant figure.
*/

/*
	Legend for suffix characters:

	01 = between 0 and 1
	10 = uses the number 10
	2  = takes two arguments if it is a function, squared if it is a variable
	e  = efficient
	f  = float specific
	i  = integer specific
	m  = uses the modulo function
	s  = simple, the human-logical way of doing things
*/

// Returns the absolute value of an integer
int   Matth::absi(const int value)
{
	int neg = value * -1;
	return (value < 0) ? (neg) : value;
}

// Returns the absolute value of a float
float  Matth::abs(const float value)
{
	float neg = value * -1;
	return (value < 0) ? (neg) : value;
}

// Returns the arccos of value
float Matth::acos(const float value)
{
	return PI / 2.0f - Matth::asin(value);
}

// Returns the arcsin of value
float Matth::asin(const float value)
{
	float valueCubed = value * value * value;
	return value + (valueCubed / 6.0f) + (3.0f * valueCubed * value * value / 40.0f);
	// 6 = 2 * 3
	// 40 = 2 * 4 * 5
}

// Returns the arctan of value in radians using a Taylor series
float Matth::atan(const float value)
{
	float valueCubed = value * value * value;
	return value - (valueCubed / 3.0f) + (valueCubed * value * value / 5.0f);
}

// The 2 parameter version of atan, returns atan(y/x) in radians, quadrant appropriate
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

// If the two values are approximately equal return true
// Rounds both x and y and compares them
// Needs improvement------------------------------------
bool Matth::approximately(const float x, const float y)
{
	return (Matth::round(x) == Matth::round(y));
}

// Returns the average of two floats
float Matth::average(const float x, const float y)
{
	return (x + y) / 2.0f;
}

// Returns the average of a float and an integer
float Matth::average(const int x, const float y)
{
	return (x + y) / 2.0f;
}

// Returns the average of 2 integers
float Matth::average(const int x, const int y)
{
	return (x + y) / 2.0f;
}

// Returns a float rounded up to an integer
int  Matth::ceili(const float value)
{
	return Matth::floori(value) + 1;
}

// Returns the same float rounded up
float Matth::ceil(const float value)
{
	return Matth::floori(value) + 1.0f;
}

// Clamps the integer value between min and max
int  Matth::clampi(const int value, const int min, const int max)
{
	if(value < min)
		return min;
	if(value > max)
		return max;
	return value;
}

// Clamps the value between min and max
float Matth::clamp(const float value, const float min, const float max)
{
	if(value < min)
		return min;
	if(value > max)
		return max;
	return value;
}

// Clamps the value between 0 and 1
int Matth::clamp01(const float value)
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

// Calculate cosine of the value using a Taylor series, in radians
float Matth::cos(const float value)
{
	float valueSquared = value * value;
	return 1.0f - (valueSquared / 2.0f) + (valueSquared * valueSquared / 24.0f);
	// 2 = 2!
	// 24 = 4!
}

// Calculate sine of the value using a Taylor series, in radians
float Matth::sin(const float value)
{
	// As always for a faster operation this is an approximation
	float valueCubed = value * value * value;
	return value - (valueCubed / 6.0f) + (valueCubed * value * value / 120.0f);
	// 6 = 3!
	// 120 = 5!
}

// Returns tan of the value in radians
float Matth::tan(const float value)
{
	float valueCubed = value * value * value;
	return value + (valueCubed / 3.0f) + (2.0f * valueCubed * value * value / 15.0f);
	//15 = 1 * 3 * 5
}

// Returns the cotangent of value
float Matth::cot(const float value)
{
	return (1.0f / value) - (value / 3.0f) - (value * value * value / 45.0f);
}

// Returns the secant of value
float Matth::sec(const float value)
{
	float valueSquared = value * value;
	return 1.0f + (valueSquared / 2.0f) + (5.0f * valueSquared * valueSquared / 24.0f);
}

// Returns the cosecant of value
// See: https://www.mathportal.org/formulas/pdf/taylor-series-formulas.pdf
float Matth::csc(const float value)
{
	return (1.0f / value) + (value / 6.0f) + (7 * value * value * value / 360);
}

// TODO
float Matth::deltaAngle(const float current, const float target)
{
	return 0.0f;
}

// Returns e to a given power using a Taylor series
float Matth::exp(const float power)
{
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

float Matth::exps(const int power)
{
	return pows(EULER_E, power);
}

// Returns the float rounded down to an integer
int  Matth::floori(const float value)
{
	return (int)Matth::floor(value);
}

// Returns the same float rounded down
float Matth::floor(const float value)
{
	// Check this works, note tenTimes is an integer
	int tenTimes = value * 10;
	return tenTimes / 10;
}

// Converts a float from linear space to gamma space
// Article about it: http://filmicworlds.com/blog/linear-space-lighting-i-e-gamma/
float Matth::linearToGammaSpace(const float value)
{
	return Matth::sqrt(value);// should really be pow 0.454545
}

// Converts a float from gamma space to linear space
float Matth::gammaToLinearSpace(const float value)
{
	return Matth::powm(value, 2);// should really be 2.2
}

// I just made this up. It should work. Could be more efficient
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

// Efficient way of determining if value is a power of 2
// Taken from: http://graphics.stanford.edu/~seander/bithacks.html
bool Matth::isPowerOfTwoe(const int value)
{
	return value && !(value & (value - 1));
}

// Here, value represents time. Linearly interpolates between start and end. Clamps to start and end
float Matth::lerp(const float start, const float end, const float value)
{
	return Matth::clamp(start + value * (end - start), start, end);
}

// TODO
float Matth::lerpAngle(const float start, const float end, const float value)
{
	return 0.0f;
}

// Linearly interpolates between start and end, using value as time
float Matth::lerpUnclamped(const float start, const float end, const float value)
{
	return start + value * (end - start);
}

// TODO
float Matth::inverseLerp(const float start, const float end, const float value)
{
	return 0.0f;
}

// Returns the logarithm of value with a base of base
float Matth::log(const int value, const int base)
{
	return Matth::ln(value) / Matth::ln(base);
}

// Returns the logarithm of value with a base of base
float Matth::log(const int value, const float base)
{
	return Matth::ln(value) / Matth::ln(base);
}

// Returns the logarithm of value with a base of base
float Matth::log(const float value, const float base)
{
	return Matth::ln(value) / Matth::ln(base);
}

// Returns the  natural logarithm of an integer
float Matth::ln(const int value)
{
	// Make sure second parameter is specified to prevent recurrsion
	return Matth::ln(value, 3);
}

// Returns the natural logarithm of a float to a given precision (if supplied)
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

// Returns the logarithm of value with base 10
float Matth::log10(const int value)
{
	return Matth::ln(value) / Matth::ln(10);
}

// Returns the logarithm of value with base 10
float Matth::log10(const float value)
{
	return Matth::ln(value) / Matth::ln(10);
}

// Returns true if either a or b are true but not both
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

// Returns the next power of 2 using binary logic
// See: https://www.hackerearth.com/practice/notes/round-a-number-to-the-next-power-of-2/
int Matth::nextPowerOfTwo(const int value)
{
	int  returnValue  =  1 ;
	
	while  ( returnValue  <=  value)
	{
		returnValue  =  returnValue  <<  1 ;
	}
	return  returnValue ;
}

// Returns the next power of 2
int Matth::nextPowerOfTwo(const float value)
{
	return Matth::nextPowerOfTwo((int)value);
}

// Quick way of finding the next power of 2 for a 32 bit value
// Again from: http://graphics.stanford.edu/~seander/bithacks.html
int Matth::nextPowerOfTwoe(const float value)
{
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

// Returns an integer of x to the power y
int  Matth::powi(const int x, const int y)
{
	return (int)Matth::pow((float)x, (float)y);
}

// Returns a float of x to the power y
float Matth::pow(const float x, const int y)
{
	return Matth::powm(x, (float)y);
}

// Returns a float x to the power of a float y
float Matth::powf(const float x, const float y)
{
	return Matth::exp(y * Matth::ln(x, 5));
}

// Simple power algorithm
float Matth::pows(const float x, const float y)
{
	if (y == 0)
		return 1.0f;
	if (x == 0)
		return 0.0f;

	float runningTotal = 1.0f;
	for (int i = 0; i < y; i++)
	{
		runningTotal *= x;
	}
	return runningTotal;
}

// Returns a float of x to the power y using the modulo
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

// Returns an integer rounded to the nearest whole number
int  Matth::roundi(const float value)
{
	return (int)Matth::round(value);
}

// Returns a float rounded to the nearest whole number
float Matth::round(const float value)
{
	int intValue = (int)value;
	float tenths = value - intValue;
	if(10 * tenths > 4)// I.e. Greater than or equal to 5
		return Matth::ceil(value);
	return intValue;
}

// Checks the sign of a given value. Returns 1 if positive, -1 if negative
int Matth::sign(const int value)
{
	return (value < 0) ? -1 : 1;
}

// Checks the sign of a given value. Returns 1 if positive, -1 if negative
int Matth::sign(const float value)
{
	return (value < 0) ? -1 : 1;
}

// Returns true if the value is positive, else false
bool Matth::isPositive(const int value)
{
	return value > 0;
}

// Returns true if the value is positive, else false
bool Matth::isPositive(const float value)
{
	return value > 0;
}

// Returns true if the value is negative, else false
bool Matth::isNegative(const int value)
{
	return value < 0;
}

// Returns true if the value is negative, else false
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

// Returns an integer of a square rooted value
int  Matth::sqrti(const int value)
{
	return (int)Matth::FIISRBOQ3C(value);
}

// Combines speed with acceptable level of accuracy 
float Matth::sqrt(const int value)
{
	return Matth::FIISRBOQ3C(value);
}

// My 13 year-old self's square root method. Newtonian? Accurate but slow (7 iterations)
// Default precision is 8 iterations but can be modified.
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

// fastInverseInverseSquareRootBasedOnQuakeIIICode
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

// Returns the sqaure root of the value using the natural logarithm
float Matth::sqrtWithNaturalLog(const float value)
{
	// log(x^0.5) = 0.5 * log(x)
	float logNum = Matth::ln(value, 100);
	float halfLogNum = logNum / 2.0f;
	return Matth::exp(halfLogNum);
}
