#pragma once
//interpolation.h

namespace Interp {

	// --x0 --------t------------x1 -------
	//        t          1-t	

	float linear(float x0, float x1, float t) {
		return (1.0f - t) * x0 + t * x1;
	}

	// --y0--------y1----t----y2-------y3--
	//   -1        0          1

	//
	float lagrangeCubic(float y0, float y1, float y2, float y3, float t) {
		return y0 * (t) * (t - 1) * (t - 2) / -6 + y1 * (t + 1) * (t - 1) * (t - 2) / 2 + y2 * (t + 1) * t * (t - 2) / -2 + y3 * (t + 1) * t * (t - 1) / 6;
	}

}

