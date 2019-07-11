#pragma once
#ifndef matrices_cpu_operations
#define matrices_cpu_operations
namespace Marices_cpu {
	void exp(double * sz, double * m1, double * m2, int n);
	void multiply(double* sz, double* m1, double* m2, int n);
	void divide(double* sz, double* m1, double* m2, int n);
	void add(double* sz, double* m1, double* m2, int n);
	void subtract(double* sz, double* m1, double* m2, int n);

	void exp(double* sz, double* m, double v, int n);
	void multiply(double* sz, double* m, double v, int n);
	void divide(double* sz, double* m, double v, int n);
	void add(double* sz, double* m, double v, int n);
	void subtract(double* sz, double* m, double v, int n);

	void dot(double* sz, double* m1, int m1_l, int m1_w, double* m2, int m2_l, int m2_2);		//m * m 
	void dot_Matrix_T_Matrix(double* sz, double* m1, int m1_l, int m1_w, double* m2, int m2_l, int m2_2);		//m * m 

	void dot_Matrix_Vector(double* sz, double* m1, int m1_l, int m1_w, double* v, int v_l);		//m * v
	void dot_Vector_Vector(double* sz, double* v1, int v1_l, double* v2, int v2_l);		//v * v
	void dot_match_dim(double * sz, double* m1, double* m2, int n);
	void dot_MatrixTrans_Matrix(double* sz, double* m1, double* m2, int n);	//m.T() * m
	void dot_Matrix_MatrixTrans(double* sz, double* m1, double* m2, int n);	//m * m.T()
	void dot_MatrixTrans_MatrixTrans(double* sz, double* m1, double* m2, int n);//m.T() * m.T()

	void dot_MatrixTrans_Vector(double* sz, double* m1, double* m2, int n);	//m.T() * v

	void copy(double* sz, double* m1, int n); //copies values of m1 to sz
	void equal(int& boolean, double* m1, double* m2, int n); //compares the values of m1 m2 returns 0 for true 1 for false -- assumes same dimensions
	void fill(double* m1, double value, int n);

	//Code exampl of single stride 
	double floor(double n) {
		int n2 = (int)n;

		if (n2 == n) { //if they are equal
			return n;
		}
		else if (n2 > n) { //if n2 = the ceil of n
			return n2 - 1;
		}
		else {
			return n2; //else n2  = n1 - the decimal
		}
	}
	static void dot_Matrix_Matrix_cpu(double* sz, double* m1, int mat1_length, int mat1_width, double* m2, int mat2_length, int mat2_width) {

		int save_size = mat1_width * mat2_length;
		int stride_size = mat1_length;

		for (int i = 0; i < save_size * stride_size; ++i) {
			int save_index = floor(i / mat1_length);

			int m1_index = i % mat1_length + floor(save_index / mat1_width) * mat1_length;
			int m2_index = (i % mat2_width) * mat2_length + (save_index % mat2_length);
			sz[save_index] += m1[m1_index] * m2[m2_index];
		}
	}
}
#endif