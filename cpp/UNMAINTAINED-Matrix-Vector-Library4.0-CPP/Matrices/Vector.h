#pragma once
#ifndef Vector_jas_h
#define Vector_jas_h
#include "Matrix.h"

class Vector: public Matrix {
	friend class Matrix;

	Vector(unsigned int length);
	Vector(std::vector<double> v);
	Vector(const Vector& v);
	Vector();
	~Vector();

	Matrix operator * (const Vector& v) const {
		updateGPU();
		v.updateGPU();

		chkBounds(v);
		Matrix r = Matrix(length(), v.length());
		dot_Vector_Vector << <n_blocks, n_threads >> > (r.gpu_matrix, gpu_matrix, m.gpu_matrix, sz);
		cudaDeviceSynchronize();

		r.assert_gpu_update();
		transposed = false;
		v.transposed = false;

		return r;
	}
};
#endif