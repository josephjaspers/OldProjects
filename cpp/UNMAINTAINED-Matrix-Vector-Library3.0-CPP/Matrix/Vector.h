#ifndef Vector_h
#define Vector_h
#include <vector>
#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <ostream>
using namespace std;
class Matrix;

class Vector {

	int l;
	int w = 1;

	double* theVector;
	bool initialized = true;

public:
	//Constructors 
	Vector();
	Vector(unsigned int length);
	Vector(const vector<double>& vect);
	Vector(const Vector& m);
	~Vector();
	Vector& operator=(const Vector& m);
	bool operator==(const Vector& m) const;
	//simple accessors
	int length() const;
	int width() const;
	int size() const;
	//mutator methods
	double& operator()(int index);
	double& operator[](int index);
	//operations 
	Vector operator ^ (const Vector & m) const;
	Vector operator/(const Vector & m) const;
	Vector operator+(const Vector & m) const;
	Vector operator-(const Vector & m) const;
	Vector operator&(const Vector & m) const;
	//operations = 
	Vector& operator^=(const Vector & m);
	Vector& operator&=(const Vector & m);
	Vector& operator/=(const Vector & m);
	Vector& operator+=(const Vector & m);
	Vector& operator-=(const Vector & m);
	//utility methods
	Vector operator^ (const double &d) const;
	Vector operator/(const double &d) const;
	Vector operator+(const double &d) const;
	Vector operator-(const double &d) const;
	Vector operator&(const double &d) const;
	//operations = 
	Vector& operator^=(const double &d);
	Vector& operator&=(const double &d);
	Vector& operator/=(const double &d);
	Vector& operator+=(const double &d);
	Vector& operator-=(const double &d);

	vector<double> getCpyVect() const;
	void print() const;
	//read/write
	static Vector read(ifstream& fileStream);
	void write(ofstream& outputStream);

	const double& get(int x) const;

private:
	inline void chkBounds(const Vector& v) const;
	inline void chkBounds(int x) const;
};
#endif
