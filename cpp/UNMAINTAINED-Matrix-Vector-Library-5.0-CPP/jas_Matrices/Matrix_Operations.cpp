/*
#include "Matrix_Operations.h"

void Matrix_Operations::copy(double * store, double * v, int n)
{
	for (int i = 0; i < n; ++i) {
		store[i] = v[i];
	}
}

bool Matrix_Operations::equal(double * m1, double * m2, int n)
{
	for (int i = 0; i < n; ++i) {
		if (m1[i] != m2[i]) {
			return false;
		}
	}
	return true;
}

void Matrix_Operations::fill(double * m, double f, int n)
{
	for (int i = 0; i < n; ++i) 
		m[i] = f;
	
}

void Matrix_Operations::max_val(double * m, double * max, int n)
{
	double max_val = m[0];
	for (int i = 1; i < n; ++i) {
		if (max_val < m[i]) {
			max_val = m[i];
		}
	}
	*max = max_val;
}

void Matrix_Operations::min_val(double * m, double * min_val, int n)
{
	double min = m[0];
	for (int i = 1; i < n; ++i) {
		if (min > m[i]) {
			min = m[i];
		}
	}
	*min_val = min;
}

void Matrix_Operations::max_index(double * m, double * max_val, int * index, int n)
{
	double max = m[0];
	index = 0;
	for (int i = 1; i < n; ++i) {
		if (max < m[i]) {
			max = m[i];
			*index = i;
		}
	}
	*max_val = max;
}

void Matrix_Operations::min_index(double * m, double * min_val, int * index, int n)
{
	double min = m[0];
	index = 0;
	for (int i = 1; i < n; ++i) {
		if (min > m[i]) {
			min = m[i];
			*index = i;
		}
	}
	*min_val = min;
}

void Matrix_Operations::power(double * s, double * m1, double * m2, int n)
{
	for (int i = 0; i < n; ++i) {
		s[i] = pow(m1[i], m2[i]);
	}
}

void Matrix_Operations::dot(double * s, double * m1, int mat1_length, int mat1_width, double * m2, int mat2_length, int mat2_width)
{
	int save_size = mat1_width * mat2_length;
	int stride_size = mat1_length;
	int n = save_size * stride_size;

	for (int i = 0; i < n; ++i)
	{
		int save_index = floor((double)i / (mat1_length));
		int m1_index = i % mat1_length + floor((double)save_index / mat1_width) * mat1_length;
		int m2_index = (i % mat2_width) * mat2_length + (save_index % mat2_length);
		s[save_index] += m1[m1_index] * m2[m2_index];
	}
}

void Matrix_Operations::divide(double * s, double * m1, double * m2, int n)
{
	for (int i = 0; i < n; ++i) {
		s[i] = m1[i] / m2[i];
	}
}

void Matrix_Operations::add(double * s, double * m1, double * m2, int n)
{
	for (int i = 0; i < n; ++i) {
		s[i] = m1[i] + m2[i];
	}
}

void Matrix_Operations::subtract(double * s, double * m1, double * m2, int n)
{
	for (int i = 0; i < n; ++i) {
		s[i] = m1[i] - m2[i];
	}
}

void Matrix_Operations::multiply(double * s, double * m1, double * m2, int n)
{
	for (int i = 0; i < n; ++i) {
		s[i] = m1[i] * m2[i];
	}
}

void Matrix_Operations::power(double * s, double * m, double v, int n)
{
	for (int i = 0; i < n; ++i) {
		s[i] = pow(m[i], v);
	}
}

void Matrix_Operations::dot(double * s, double * m, double v, int n)
{
	s = 0;
	for (int i = 0; i < n; ++i) {
		*s += m[i] * v;
	}
}

void Matrix_Operations::divide(double * s, double * m, double v, int n)
{
	for (int i = 0; i < n; ++i) {
		s[i] = m[i] / v; 
	}
}

void Matrix_Operations::add(double * s, double * m, double v, int n)
{
	for (int i = 0; i < n; ++i) {
		s[i] = m[i] + v;
	}
}

void Matrix_Operations::subtract(double * s, double * m, double v, int n)
{
	for (int i = 0; i < n; ++i) {
		s[i] = m[i] - v;
	}
}

void Matrix_Operations::multiply(double * s, double * m, double v, int n)
{
	for (int i = 0; i < n; ++i) {
		s[i] = m[i] * v;
	}
}
*/