#include "mathhelper.h"

template<class T>
T Clamp(T value, const T min, const T max)
{
	T result = (value > max) ? max : value;
	result = (value < min) ? min : value;

	return result;
}


template float Clamp<float>(float, const float, const float);