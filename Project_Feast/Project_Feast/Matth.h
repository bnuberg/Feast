#pragma once

/*
	This is the header file for the Matth class.
	It is not a type-o. Matth is an abbreviation of Matthew.
	Coincidentally, it is also the class that handles the
	mathematical functions.
	
	The trouble with past-me is he thinks he's funny.
	
	This particular library is designed with speed over
	accuracy in mind.
*/

// NB: I haven't tested this type of macro before so idk if it works.
#define RAD_TO_DEG(angle) (angle * 57.2958f)
#define DEG_TO_RAD(angle) (angle * 0.0174533f)

#define MOD 		  1000000007
#define EPSILON       0.00000000001f
// NB: Epsilon should be scaled with the floats it is being applied to. This is a TODO.

//#define INFINITY      9999999999999f
//#define NEGATIVE_INFINITY (-1.0f * INFINITY)

#define PI            3.14159265359f
#define EULER_E       2.71828182846f

#define HALF          0.50f
#define THREE_HALF    1.50f
#define THIRD         0.33333333333f
#define TWO_THIRD     0.66666666666f
#define QUARTER       0.25f
#define THREE_QUARTER 0.75f
#define FIFTH         0.20f
#define TWO_FIFTH     0.40f
#define THREE_FIFTH   0.60f
#define FOUR_FIFTH    0.80f

class Matth
{
public:
	
	static int   absi				(const int   value);
	static float abs				(const float value);
	
	static float acos				(const float value);
	static float asin				(const float value);
	static float atan				(const float value);
	static float atan2				(const float x, const float y);
	
	static bool  approximately		(const float x, const float y);
	static float average			(const float x, const float y);
	static float average			(const int   x, const float y);
	static float average			(const int   x, const int   y);
	
	static int   ceili				(const float value);
	static float ceil				(const float value);
	static int   clampi				(const int   value, const int   min, const int   max);
	static float clamp				(const float value, const float min, const float max);
	static int   clamp01			(const float value);
	static int   closestPowerOfTwo	(const float value); // TODO
	static int   closestPowerOfTwo	(const int   value); // TODO
	
	static float cos				(const float value);
	static float sin				(const float value);
	static float tan				(const float value);
	
	static float cot				(const float value);
	static float sec				(const float value);
	static float csc				(const float value);
	
	static float deltaAngle			(const float current, const float target); // TODO
	
	static float exp				(const float power);
	static float exps				(const int power);
	
	static int   floori				(const float value);
	static float floor				(const float value);
	
	static float linearToGammaSpace (const float value);
	static float gammaToLinearSpace (const float value);
	
	static bool  isPowerOfTwo		(const int value);
	static bool  isPowerOfTwoe		(const int value);
	
	static float lerp				(const float start, const float end, const float value);
	static float lerpAngle			(const float start, const float end, const float value); // TODO
	static float lerpUnclamped		(const float start, const float end, const float value);
	static float inverseLerp		(const float start, const float end, const float value); // TODO - This should be an easy one
 
	static float log				(const int   value, const int   base);
	static float log				(const int   value, const float base);
	static float log				(const float value, const float base);
	static float ln					(const int   value);
	static float ln					(const float value, int prec = 3);
	static float log10				(const int   value);
	static float log10				(const float value);

	static bool  logicalXOR			(const bool a, const bool b);
	
	// These already exist as macros
//	static int   maxi				(const int   x, const int   y);
//	static float max				(const float x, const float y);
//	static int   mini				(const int   x, const int   y);
//	static float min				(const float x, const float y);
	
	static float moveTowards		(const float current, const float target, const float maxDelta); // TODO
	static float moveTowardsAngle	(const float current, const float target, const float maxDelta); // TODO
	
	static int  nextPowerOfTwo		(const int   value);
	static int  nextPowerOfTwo		(const float value);
	static int  nextPowerOfTwoe		(const float value);
	
	static float perlinNoise		(const float x, const float y);			 // TODO
	static float pingPong			(const float value, const float length); // TODO
	
	static int   powi				(const int   x, const int   y);
	static float powm				(	   int   x,       int   y);
	static float pow				(const float x, const int   y);
	static float powf				(const float x, const float y);
	static float pows				(const float x, const float y);
	
	static float repeat				(const float value, const float length); // TODO
	
	static int   roundi				(const float value);
	static float round				(const float value);
	
	static int   sign				(const int   value);
	static int   sign				(const float value);
	static bool  isPositive			(const int   value);
	static bool  isPositive			(const float value);
	static bool  isNegative			(const int   value);
	static bool  isNegative			(const float value);
	
	// Skipping a few recommended functions, if we really need them you can add them later
	/*
		smoothDamp
		smoothDampAngle
		smoothStep
	*/
	
	static int   sqrti				(const int   value);
	static float sqrt				(const int   value);
	static float sqrt				(const float value, int prec = 8);
	static float FIISRBOQ3C			(const float value);
	static float sqrtWithNaturalLog (const float value);
};