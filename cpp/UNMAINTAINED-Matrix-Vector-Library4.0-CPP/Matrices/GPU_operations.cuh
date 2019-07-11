#ifndef matrices_gpu_opers_h
#define matrices_gpu_opers_h

#include "cuda.h"
#include <cuda.h>
#include "cuda_runtime.h"
//#include "math_functions.h"
#include <iostream>
#include "device_launch_parameters.h"
#include "cuda_device_runtime_api.h"
#include "device_functions.h"
#include <device_functions.h>
#include <cuda_runtime_api.h>

//#include <cuda.h>
//#include <cuda_runtime_api.h>
//#include <device_launch_parameters.h>
namespace Matrices_gpu {
	//Cuda Matrix operations -- s = save/store is assumed to be a Vector or with elements set to 0
	__global__ void copy(double* sz, double* m1, int n); //copies values of m1 to sz
	__global__ void equal(bool* boolean, double* m1, double* m2, int n); //compares the values of m1 m2 returns 0 for true 1 for false -- assumes same dimensions
	__global__ void fill(double* m1, double value, int n);
	__global__ void transpose(double*s, double*m, int x, int y);

	__global__ void dot(double* s, double* m1, int m1_l, int m1_w, double* m2, int m2_l, int m2_2);		//m * m 
	__global__ void dot_transpose(double * s, double * m1, int mat1_length, int mat1_width, double * m2, int mat2_length, int mat2_width);

	__global__ void exp(double * s, double * m1, double * m2, int n);
	__global__ void multiply(double* s, double* m1, double* m2, int n);
	__global__ void divide(double* s, double* m1, double* m2, int n);
	__global__ void add(double* s, double* m1, double* m2, int n);
	__global__ void subtract(double* s, double* m1, double* m2, int n);

	__global__ void exp(double* s, double* m, double v, int n);
	__global__ void multiply(double* s, double* m, double v, int n);
	__global__ void divide(double* s, double* m, double v, int n);
	__global__ void add(double* s, double* m, double v, int n);
	__global__ void subtract(double* s, double* m, double v, int n);

	//optimized variants of common dot product situations --- if using a transposition dot product please give the original length/widths 
	//__global__ void inner_dot(double& s, double *v1, int v1_start, int inc_v1, double* v2, int v2_index, int inc_v2, int n);
	
	
	__global__ void dot_Vector_Vector(double* s, double* v1, double* v2, int n);													//computation = O(n^2) // outer product 
	__global__ void dot_Vector_Vector_inner(double* s, double* v1, double* v2, int n);
	__global__ void dot_Matrix_T_Matrix(double* sz, double* m1, int m1_l, int m1_w, double* m2, int m2_l, int m2_2);		//m * m 		//dot product of two transposed matrices 
	__global__ void dot_Matrix_Matrix_T(double* sz, double* m1, int m1_l, int m1_w, double* m2, int m2_l, int m2_2);		//m * m 		//dot product of two transposed matrices 
	__global__ void dot_Matrix_T_Matrix_T(double* sz, double* m1, int m1_l, int m1_w, double* m2, int m2_l, int m2_2);		//m * m 		//dot product of two transposed matrices 


	//Code exampl of single stride 
	static void dot_Matrix_Matrix_cpu(double* sz, double* m1, int mat1_length, int mat1_width, double* m2, int mat2_length, int mat2_width) {

		int save_size = mat1_width * mat2_length;
		int stride_size = mat1_length;

		for (int i = 0; i < save_size * stride_size; ++i) {
			int save_index = floor(i / (mat1_length));

			int m1_index = i % mat1_length + floor(save_index / mat1_width) * mat1_length;
			int m2_index = (i % mat2_width) * mat2_length + (save_index % mat2_length);
			sz[save_index] += m1[m1_index] * m2[m2_index];
		}
	}

	__global__ void reshape(double* s, double* m1, int x, int y);
}
#endif


