#pragma once
#ifndef Matrix_h
#define Matrix_h
#include <iostream>
#include <vector>
#include <fstream>
#include <ostream>
#include "Matrix_Operations.h"

using namespace Matrix_Operations;	
class Vector;

class Matrix {
	friend class Vector;
protected:
	unsigned x;
	unsigned y;
	unsigned n;

	double* matrix;
	bool initialized;

public:
	//Constructors
	Matrix();
	Matrix(unsigned int width);
	Matrix(unsigned int length, unsigned int width);
	Matrix(const std::vector<std::vector<double>>& m);
	Matrix(std::vector<double> mat, int length, int width);
	Matrix(const Matrix& cpy);
	~Matrix();
	//simple accessors 
	bool isInitialized() const;
	int length() const;
	int width() const;
	int size() const;

	double& operator[] (int index);
	//cpy operator 
	Matrix& operator=(const Matrix & m);								//copy Matrix (must be of same dimensions)
	Matrix& copy_elements(const Matrix& m);						//copies elements of the given Matrix with same dimenions n
	//compare operator
	bool operator== (const Matrix & m) const;
	//dot products
	Matrix operator*(const Matrix & m) const;
	Matrix operator->*(const Matrix& m) const;
	//dot products (with Vectors) defined in Vector.cpp (for compilation purposes)
	Vector operator* (const Vector & v) const;
	Vector operator->* (const Vector & v) const;

	Matrix operator^(const Matrix & m) const;
	Matrix operator/(const Matrix & m) const;
	Matrix operator+(const Matrix & m) const;
	Matrix operator-(const Matrix & m) const;
	Matrix operator&(const Matrix& m) const;
	Matrix& operator^=(const Matrix & m);
	Matrix& operator/=(const Matrix & m);
	Matrix& operator+=(const Matrix & m);
	Matrix& operator-=(const Matrix & m);
	Matrix& operator&=(const Matrix& m);

	Matrix operator^(const double& d) const;
	Matrix operator/(const double& d) const;
	Matrix operator+(const double& d) const;
	Matrix operator-(const double& d) const;
	Matrix operator&(const double& d) const;
	Matrix& operator^=(const double& d);
	Matrix& operator/=(const double& d);
	Matrix& operator+=(const double& d);
	Matrix& operator-=(const double& d);
	Matrix& operator&=(const double& d);

	double max() const;
	double min() const;
	double max_id(int& x, int& y);
	double min_id(int& x, int& y);
	double max_id(int& i);
	double min_id(int& i);

	Matrix& fill(double v);
	static void fill(Matrix& m, double v);

	bool isColumnVector() const;
	bool isRowVector() const;
	Matrix transpose() const;
	Matrix T() const;

	void print() const;
	void print(int p) const;

	static Matrix read(std::ifstream & f);
	void write(std::ofstream & o);

	const double& get(int x, int y) const;
	void printDim() const;

public:

	//DANGER THIS RETURNS THE INSIDE MATRIX - DO NOT DELETE AS ERROR WILL BE THROWN WHEN DECONSTRUCTOR - USE WITH CAUTION
	double* getInternals();
	const double* getInternals_const() const;
protected:
	void initialize();
public:
	void chkBounds(const Matrix& m) const;
	void dot_chkBounds(const Matrix& m) const;
	void dot_transpose_chkBounds(const Matrix & m) const;
	void chkBounds(int x, int y) const;
};

#endif