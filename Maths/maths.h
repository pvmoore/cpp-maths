#pragma once

namespace maths {

inline const float PI = 3.141592653589793f;

inline constexpr float toRadians(float degs) {
	return degs * PI / 180.0f;
}
inline constexpr float toDegrees(float rads) {
	return rads * 180.0f / PI;
}
inline constexpr bool approxEqual(float a, float b) {
	return a == b || std::abs(a - b) <= 0.0001f;
}
std::vector<unsigned int> factorsOf(unsigned int n);

}

#include "vector2.h"
#include "vector3.h"
#include "vector4.h"
#include "matrix4.h"
#include "camera.h"
#include "camera2d.h"
#include "camera3d.h"
