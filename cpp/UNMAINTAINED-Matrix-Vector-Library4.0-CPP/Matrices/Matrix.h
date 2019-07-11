#pragma once
#ifndef Matrix_jas_h
#define Matrix_jas_h

#include "GPU_Specs.h"
#include "GPU_operations.cuh"
#include <vector>
#include <iostream>
using namespace Matrices_gpu;
using namespace GPU_specs;
class Matrix {
protected:
	/*
	Some Formulas 
							[Given the limitation of the Matrix representation using a single array] : i is used to notate index from i = 0 to n elements.  : x = horizontal length, y = vertical length
		Transpose: 
			Index = i * x + floor(i / y)
		Dot Product:
			int save_index = floor((double)i / (mat1_length));
			int m1_index = i % mat1_length + floor((double)save_index / mat1_width) * mat1_length;
			int m2_index = (i % mat2_width) * mat2_length + (save_index % mat2_length);
			sz[save_index] += m1[m1_index] * m2[m2_index];
		For O(n) operations:
			inputs=>(x_in, y_in)
				x_in + y_in * x
	
	
	*/
	bool initialized = false;	//Determines if gpu_matrix is initialized								
	void initialize();			//initializes memory of the matrices.

	int x_dim;					//the length or x-axis dimension of the gpu_matrix
	int y_dim;					//the width or y-axis dimension of the gpu_matrix
	int sz;						//size of the gpu_matrix (number of elements)

	mutable bool cpu_update = false;			//True if cpu_matrix has been modified (and the cpu_matrix != gpu_matrix)
	mutable bool gpu_update = false;	//True if gpu_matrix has been modified (and the gpu_matrix != cpu_matrix)

	bool updateCPU() const;			//copies gpu_matrix elements to cpu_matrix || returns true if gpu was updated (false does not mean failure - checks cache if needs update)
	bool updateGPU() const;			//copies cpu_matrix elements to gpu_matrix || returns true if cpu was updated (false does not mean failure - checks cache if needs update)

	int n_blocks = 256;			//number of blocks run on gpu_matrix calls (will update later)
	int n_threads = 256;		//number of threads run on gpu_matrix calls (willupdate later);

	double* cpu_matrix;			//Matrix data kept on CPU memory. Updates only when host-side needs access to it.
	double* gpu_matrix;			//Matrix data kept on GPU memory. Handles a majority of the computations.
public:
	void assert_cpu_update(bool update= true);				//modify the cpu_update boolean value
	void assert_gpu_update(bool update= true);				//modify the gpu_update boolean value
	void force_cpu_update();								//update cpu in respects to gpu (copies)
	void force_gpu_update();								//update gpu in respects to cpu (copies)

public:
	Matrix(unsigned int length, unsigned int width);
	Matrix(std::vector<double> m, int x, int y);
	Matrix(std::vector<std::vector<double>> m);
	Matrix(const Matrix& cpy);
	Matrix();
	~Matrix();

	int length() const;
	int width() const;
	int size() const;

	void print();				//print gpu_mdtrix to console, not recommended for large matrices.
	void print(int p);			//print gpu_matrix to console with cout.precision set to int p.
	
	void write(std::ofstream & o) const;		//write gpu_matrix as text to file
	void read(std::ifstream & i) const;			//read gpu_matrix from a text file
	
	double& operator[] (int i);							//access cpu gpu_matrix (direct double reference) -- updates the cpu_matrix if needed
	double& operator() (int x, int y);					//access cpu gpu_matrix by (x,y) dimensions -- updates cpu_matrix if needed
	Matrix& operator = (const Matrix& m);				//copies gpu gpu_matrix of same dimensions, matrices are non mutable in dimensions.

	virtual Matrix T();								//transposes the matrix, --> the transposed state will end after the next operation with another Matrix
	virtual Matrix transpose() const;					//generates a new matrix and returns the transposition of it.

	void fill(double v);								//Fill Matrix double value

	Matrix operator ^ (const Matrix& m) const;			//pointwise exponentiation
	Matrix operator * (const Matrix& m) const;			//dot product
	Matrix operator ->* (const Matrix& m) const;		//dot product (*this transposed)
	Matrix operator & (const Matrix& m) const;			//pointwise multiplication
	Matrix operator / (const Matrix& m) const;			//pointwise division
	Matrix operator + (const Matrix& m) const;			//pointwise addition
	Matrix operator - (const Matrix& m) const;			//pointwise subtraction

	Matrix& operator ^= (const Matrix& m);				//pointwise exponentiation and set
	Matrix& operator &= (const Matrix& m);				//pointwise multiplication and set
	Matrix& operator /= (const Matrix& m);				//pointwise division and set
	Matrix& operator += (const Matrix& m);				//pointwise addition and set
	Matrix& operator -= (const Matrix& m);				//pointwise subtraction and set

	Matrix operator^(double v) const;					//scalar exponenet
	Matrix operator/(double v) const;					//scalar division
	Matrix operator+(double v) const;					//scalar addition
	Matrix operator-(double v) const;					//scalar subtraction
	Matrix operator&(double v) const;					//scalar multiplication

	Matrix& operator^=(double v);						//scalar exponentation and set
	Matrix& operator/=(double v);						//scalar division and set
	Matrix& operator+=(double v);						//scalar addition and set
	Matrix& operator-=(double v);						//scalar subtractino and set
	Matrix& operator&=(double v);						//scalar multiplication and set

protected:
	void chkBounds(const Matrix& m) const;
	void chkBounds_dotProduct(const Matrix& m) const;
	void chkBounds_dotProduct_transposed(const Matrix& m) const;

	void chkBounds_dot_dimensions(const Matrix& m1, const Matrix& m2) const;
	void chkBounds(const Matrix& m, std::string message) const;
	void chkBounds_dotProduct(const Matrix& m, std::string message) const;
	void chkBounds_dot_dimensions(const Matrix& m1, const Matrix& m2, std::string message) const;
};
#endif
