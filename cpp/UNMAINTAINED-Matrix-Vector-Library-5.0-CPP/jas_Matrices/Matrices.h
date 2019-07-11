#pragma once
#ifndef Matrices_h
#define Matrices_h
#include "Matrix.h"
#include "Vector.h"

namespace Matrices {

	static void randomize(Matrix& m, int lower_bound, int upper_bound) {
		for (int i = 0; i < m.size(); ++i) {
			m[i] = rand() % (upper_bound - lower_bound) + lower_bound;
		}
	}
	static void randomize(Vector& m, int lower_bound, int upper_bound) {
		for (int i = 0; i < m.size(); ++i) {
			m[i] = rand() % (upper_bound - lower_bound) + lower_bound;
		}
	}
};
#endif