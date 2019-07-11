
#pragma once
#ifndef jas_Vector_h
#define jas_Vector_h

#include "Matrix.h"

using namespace Matrix_Operations;
class Vector {
	friend class Matrix;
	bool isColVector = true;
	
protected:
	unsigned int x; //length always = 1
	unsigned int y;
	unsigned int n;

	double* vector;
	bool initialized = false;

public:
	//Constructors
	Vector();
	Vector(unsigned int width);
	Vector(const Vector& cpy);
	Vector(std::vector<double> v);
	~Vector();
	//simple accessors 
	double& operator[] (int index);
	bool isInitialized() const;
	int length() const;
	int width() const;
	int size() const;
	//copy / equality 
	Vector& operator=(const Vector & m);						//copy Vector (must be of same dimensions)																//compare operator
	bool operator== (const Vector & m) const;
	//dot products -- 
	Matrix operator->*(const Vector& m) const;		//outer product
	double operator * (const Vector& v) const;		//inner produc
	double operator * (const double& d) const;		//inner product
	//operators pointwise
	Vector operator^(const Vector & m) const;
	Vector operator/(const Vector & m) const;
	Vector operator+(const Vector & m) const;
	Vector operator-(const Vector & m) const;
	Vector operator&(const Vector& m) const;
	Vector& operator^=(const Vector & m);
	Vector& operator/=(const Vector & m);
	Vector& operator+=(const Vector & m);
	Vector& operator-=(const Vector & m);
	Vector& operator&=(const Vector& m);
	//operators pointwise
	Vector operator^(const double& d) const;
	Vector operator/(const double& d) const;
	Vector operator+(const double& d) const;
	Vector operator-(const double& d) const;
	Vector operator&(const double& d) const;
	Vector& operator^=(const double& d);
	Vector& operator/=(const double& d);
	Vector& operator+=(const double& d);
	Vector& operator-=(const double& d);
	Vector& operator&=(const double& d);

	double max() const;
	double min() const;
	double max_id(int& x, int& y);
	double min_id(int& x, int& y);
	double max_id(int& i);
	double min_id(int& i);

	Vector& fill(double v);
	static void fill(Vector& m, double v);

	void print() const;
	void print(int p) const;

	static Vector read(std::ifstream & f);
	void write(std::ofstream & o);

	const double& get(int x, int y) const;

protected:
	void initialize();
public:
	void chkBounds(const Vector& m) const;
	void dot_chkBounds(const Vector& m) const;
	void dot_transpose_chkBounds(const Vector & m) const;
	void chkBounds(int x, int y) const;

};
#endif
