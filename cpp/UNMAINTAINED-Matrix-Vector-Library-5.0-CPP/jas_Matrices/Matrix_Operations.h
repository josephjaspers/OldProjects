#pragma once
#ifndef Matrices_jas_operations_h
#define Matrices_jas_operations_h
#include <math.h>
#include <cstdlib>
namespace Matrix_Operations {
	/*
	Naming Conventions
	s = save/store location 
	m = matrix 
	v = vector 
	n = size 


	Some algorthims -- getting transposed index
		for (int i = 0; i < n; ++i)
		save[index] = matrix at index -> i % y * x + (int)floor(i / y) % x
	*/
	

	inline  void copy(double* store, const double* v, int n);
	inline  bool equal(double* m1, const double* m2, int n);
	inline  void fill(double* m, double f, int n);
	inline  void transpose(double* s, const double* m, int x_dim, int y_dim);

	inline  void max_val(const double* m, double* max_val, int n);
	inline  void min_val(const double* m, double* min_val, int n);
	inline  void max_index(const double * m, double * max_val, int * index, int n);
	inline  void min_index(const double * m, double * min_val, int * index, int n);

	inline  void dot_inner(double& s, const double* v1, const double* v2, int n);
	inline  void dot_outer(double * s, const double* v1, int l1, const double* v2, int l2);
	inline	void dot_transpose(double* s, const double* m1, int m1_l, int m1_width, const double* m2, int m2_length, int m2_width);

	inline  void power(double* s, const double* m1, const double* m2, int n);
	inline  void dot(double* s, const double* m1, int mat1_length, int mat1_width, const double* m2, int mat2_length, int mat2_width); //dot product 
	inline  void divide(double* s, const double* m1, const double* m2, int n);
	inline  void add(double* s, const double* m1, const double* m2, int n);
	inline  void subtract(double* s, const double* m1, const double* m2, int n);
	inline  void multiply(double* s, const double* m1, const double* m2, int n);

	inline  void power(double *s, const double *m, double v, int n);
	inline  void dot(double *s, const double *m, double v, int n); //inner dot with constant 
	inline  void divide(double *s, const double *m, double v, int n);
	inline  void add(double *s, const double *m, double v, int n);
	inline  void subtract(double *s, const double *m, double v, int n);
	inline  void multiply(double *s, const double *m, double v, int n);
};

void Matrix_Operations::copy(double * store, const double * v, int n)
{
	#pragma omp parallel for
	for (int i = 0; i < n; ++i) {
		store[i] = v[i];
	}
}

bool Matrix_Operations::equal(double * m1, const double * m2, int n)
{
	//#pragma omp parallel for 
	for (int i = 0; i < n; ++i) {
		if (m1[i] != m2[i]) {
			return false;
		}
	}
	return true;
}

void Matrix_Operations::fill(double * m, double f, int n)
{
	#pragma omp parallel for
	for (int i = 0; i < n; ++i)
		m[i] = f;
}

void Matrix_Operations::max_val(const double * m, double * max, int n)
{
	double max_val = m[0];
#pragma omp parallel for
	for (int i = 1; i < n; ++i) {
		if (max_val < m[i]) {
			max_val = m[i];
		}
	}
	*max = max_val;
}

void Matrix_Operations::min_val(const double * m, double * min_val, int n)
{
	double min = m[0];
#pragma omp parallel for
	for (int i = 1; i < n; ++i) {
		if (min > m[i]) {
			min = m[i];
		}
	}
	*min_val = min;
}

void Matrix_Operations::max_index(const double * m, double * max_val, int * index, int n)
{
	double max = m[0];
	index = 0;
#pragma omp parallel for
	for (int i = 1; i < n; ++i) {
		if (max < m[i]) {
			max = m[i];
			*index = i;
		}
	}
	*max_val = max;
}

void Matrix_Operations::min_index(const double * m, double * min_val, int * index, int n)
{
	double min = m[0];
	index = 0;
#pragma omp parallel for
	for (int i = 1; i < n; ++i) {
		if (min > m[i]) {
			min = m[i];
			*index = i;
		}
	}
	*min_val = min;
}


void Matrix_Operations::power(double * s, const double * m1, const double * m2, int n)
{
#pragma omp parallel for
	for (int i = 0; i < n; ++i) {
		s[i] = pow(m1[i], m2[i]);
	}
}

void Matrix_Operations::dot(double * s, const double * m1, int mat1_length, int mat1_width, const double * m2, int mat2_length, int mat2_width)
{
	int save_size = mat1_width * mat2_length;
	int stride_size = mat1_length;
	int n = save_size * stride_size;

#pragma omp parallel for
	for (int i = 0; i < n; ++i)
	{
		int save_index = floor(i / (mat1_length));
		//std::cout << " save index is " << save_index << "evaluated width is ..... "  <<  floor(save_index/mat2_length) * mat1_length << std::endl;
		int m1_index = i % mat1_length + floor(save_index / mat2_length) * mat1_length;
		int m2_index = (i % mat2_width) * mat2_length + (save_index % mat2_length);
		
		s[save_index] += m1[m1_index] * m2[m2_index];
		//std::cout << "s[" << save_index << "] = " << s[save_index]  << " added " << m1[m1_index] << " * " << m2[m2_index] << " = " << m1[m1_index] * m2[m2_index] << std::endl;
	}	
}

void Matrix_Operations::dot_inner(double & s, const double * v1, const double * v2, int n)
{
	s = 0;
#pragma omp parallel for
	for (int i = 0; i < n; ++i) {
		s += v1[i] * v2[i];
	}
}

void Matrix_Operations::dot_outer(double * s, const double * v1, int l1, const double * v2, int l2)
{
#pragma omp parallel for 
	for (int l = 0; l < l1; ++l) {
		for (int w = 0; w < l2; ++w) {
			s[l1 + w * l2] = v1[l] * v2[w];
		}
	}

	/*
	int s_index = 0;

//#pragma omp parallel for //collapse(2)
	for (int i = 0; i < l2; ++i) {
		for (int j = 0; j < l1; ++j) {
			s[s_index] = v1[j] * v2[i];
			++s_index;
		}
	}
	*/
}

void Matrix_Operations::dot_transpose(double * s, const double * m1, int mat1_length, int mat1_width, const double * m2, int mat2_length, int mat2_width)
{
	int save_size = mat1_length * mat2_length;
	int stride_size = mat2_width;
	int n = save_size * stride_size;

#pragma omp parallel for
	for (int i = 0; i < n; ++i)
	{
		int save_index = floor(i / (mat1_width));
		int m1_index = (i % mat1_width) * mat1_length + ((int)floor((i / mat1_length) / mat1_width));
		int m2_index = (i % mat2_width) * mat2_length + (save_index % mat2_length);
		s[save_index] += m1[m1_index] * m2[m2_index];
		//std::cout << "s[" << save_index << "] = " << s[save_index]  << " added " <<m1[ m1_index] << " * " << m2[m2_index] << " = " << m1[m1_index] * m2[m2_index] << std::endl;
	}
}



void Matrix_Operations::divide(double * s, const double * m1, const double * m2, int n)
{
#pragma omp parallel for
	for (int i = 0; i < n; ++i) {
		s[i] = m1[i] / m2[i];
	}
}

void Matrix_Operations::add(double * s, const  double * m1, const double * m2, int n)
{
#pragma omp parallel for
	for (int i = 0; i < n; ++i) {
		s[i] = m1[i] + m2[i];
	}
}

void Matrix_Operations::subtract(double * s, const double * m1, const  double * m2, int n)
{
#pragma omp parallel for
	for (int i = 0; i < n; ++i) {
		s[i] = m1[i] - m2[i];
	}
}

void Matrix_Operations::multiply(double * s, const double * m1, const double * m2, int n)
{
#pragma omp parallel for
	for (int i = 0; i < n; ++i) {
		s[i] = m1[i] * m2[i];
	}
}

void Matrix_Operations::power(double * s, const double * m, double v, int n)
{
#pragma omp parallel for
	for (int i = 0; i < n; ++i) {
		s[i] = pow(m[i], v);
	}
}

void Matrix_Operations::dot(double * s, const  double * m, double v, int n)
{
	s = 0;
#pragma omp parallel for
	for (int i = 0; i < n; ++i) {
		*s += m[i] * v;
	}
}

void Matrix_Operations::divide(double * s, const double * m, double v, int n)
{
#pragma omp parallel for
	for (int i = 0; i < n; ++i) {
		s[i] = m[i] / v;
	}
}

void Matrix_Operations::add(double * s, const double * m, double v, int n)
{
#pragma omp parallel for
	for (int i = 0; i < n; ++i) {
		s[i] = m[i] + v;
	}
}

void Matrix_Operations::subtract(double * s, const double * m, double v, int n)
{
#pragma omp parallel for
	for (int i = 0; i < n; ++i) {
		s[i] = m[i] - v;
	}
}

void Matrix_Operations::multiply(double * s, const double * m, double v, int n)
{
#pragma omp parallel for
	for (int i = 0; i < n; ++i) {
		s[i] = m[i] * v;
	}
}

void Matrix_Operations::transpose(double * s, const double * m, int x, int y) {
	//Yes this transposes
#pragma omp parallel for
	for (int i = 0; i < x * y; ++i) {
		s[i] = m[i % y * x + (int)floor(i / y) % x];
	}
}
#endif