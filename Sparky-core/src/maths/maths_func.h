#pragma once
#include <math.h>
#define _USE_MATH_DEFINES
#define M_PI       3.14159265358979323846

namespace sparky { namespace maths {
		inline float toRadians(float degrees)
		{
			return degrees * (M_PI / 180.0f);
		}
	}
}
