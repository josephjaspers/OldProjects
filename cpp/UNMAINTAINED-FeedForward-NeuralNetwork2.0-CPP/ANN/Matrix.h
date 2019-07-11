#ifndef Matrix_h
#define Matrix_h
#include <cstdlib>
#include <vector>
#include <cmath>
#include <iostream>
#include "stdafx.h"
#include <exception>
#include <ostream>
#include <fstream>
#include <memory>
using namespace std;

class Matrix {
	int l;
	int w;
	int n;

	bool transposed = false;

	vector<double> theMatrix;

public:
	Matrix() {}
	Matrix(unsigned int length, unsigned int width);
	Matrix(unsigned int length);
	Matrix(const vector<double>& vect);
	Matrix(const vector<vector<double> >& m);
	//cpy constructor
	Matrix(const Matrix& m);
	//cpy assignment
	void operator=(const Matrix& m);
	//comparator
	bool operator==(const Matrix& m) const;
	//simple accessors
	int length() const;
	int width() const;
	int size() const;
	//mutator methods
	inline double& operator()(int length, int width);
	inline double& operator[](int index);
	//operations 
	unique_ptr<Matrix> operator ^ (const Matrix & m) const;
	unique_ptr<Matrix> operator*(const Matrix & m) const;
	unique_ptr<Matrix> operator/(const Matrix & m) const;
	unique_ptr<Matrix> operator+(const Matrix & m) const;
	unique_ptr<Matrix> operator-(const Matrix & m) const;
	unique_ptr<Matrix> x(const Matrix & m) const;
	//operations = 
	Matrix& operator^=(const Matrix & m);
	Matrix& operator*=(const Matrix & m);
	Matrix& operator/=(const Matrix & m);
	Matrix& operator+=(const Matrix & m);
	Matrix& operator-=(const Matrix & m);
	//utility methods
	//* getColumn and getRow both return column vectors opposed to a single column unique_ptr<Matrix> and a single row unique_ptr<Matrix>
	unique_ptr<Matrix> getColumn(unsigned int col) const;
	unique_ptr<Matrix> getRow(unsigned int row) const;
	bool isColumnVector() const;
	bool isRowVector() const;
	unique_ptr<Matrix> transpose() const;

	Matrix& T() {
		if (transposed) {
			transposed = false;
		}
		else {
			transposed = true;
		}
		return *this;
	}

	vector<double> getCpyVect() const;

	void print() const;
	void print(int p) const;
	//read/write
	Matrix& read(ifstream& fileStream);
	void write(ostream& outputStream);

private:
	inline int index(unsigned int l, unsigned int w) const;
};
#endif