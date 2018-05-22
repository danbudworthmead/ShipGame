#pragma once

#include <type_traits>


// we define this because a definition in math.h is unreliable since M_PI is a nonstandard macro, only defined in the POSIX standard
#define M_PI 3.14159265358979323846	

#define DEG2RAD(degrees) ((degrees) * M_PI / 180.0)
#define RAD2DEG(radians) ((radians) * 180.0 / M_PI)

template<class T>
T Clamp(T value, const T min, const T max);

