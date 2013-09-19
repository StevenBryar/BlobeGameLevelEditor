#ifndef MYMATH_H
#define MYMATH_H

#include <cmath>
#include "Vector2.h"
#include "Vector3.h"

#define PI 3.141592
#define PIOver2 PI/2
#define PIOver4 PI/4
#define OneEightyOverPI 180/PI
#define TwoPi PI*2

//Max		returns the greater value
template<typename T>
T Max(T v1,T v2)
{ 
	return (v1 > v2 ? v1:v2);
}

//Min		returns the lesser value
template<typename T>
T Min(T v1,T v2)
{ 
	return (v1 < v2 ? v1:v2);
}

//Clamp			Clamps a value to be between two other values
template<typename T>
T Clamp(T min,T value,T max)
{ 
	if(value == Max<T>(value,max))
		return max;
	if(value == Min<T>(value,min))
		return min;

	return value;
}

//Lerp			Performs a linear interpolation between to values.
template<typename T>
T Lerp(T v1,T v2,float amount)
{ 
	return v1 + (v2 - v1) * amount;
}

/*Ceil		Returns the smallest whole number 
				greater than or equal to the specified number.*/
inline float Ceil(float v)
{
	int intv = v;
	if(intv - v == 0)
		return intv;

	return intv + (v > 0 ? 1:0);
}

/*Floor		Returns the largest whole number 
				less than or equal to the specified number.*/
inline float Floor(float v)
{
	float CeilV = Ceil(v);

	return(CeilV == v ? v : CeilV-1);
}

#endif


