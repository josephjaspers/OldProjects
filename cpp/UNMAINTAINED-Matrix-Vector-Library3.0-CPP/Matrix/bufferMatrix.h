#pragma once
#ifndef buffMatrix_h
#define buffMatrix_h
#include "Matrix.h"
#include <vector>

using namespace std;

struct operBuffer {
	Matrix* storeMatrix;
	virtual Matrix& eval(Matrix& m) = 0;
};
struct multBuffer : public operBuffer {
	Matrix& eval(Matrix& m) {
		for (int x = 0; x < m.length; ++x) {
			for (int y = 0; y < m.width; ++y) {
				m(x,y) *= (*storeMatrix)(x,y);
			}
		}
	}
};
#endif