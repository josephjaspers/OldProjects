#include "stdafx.h"
#pragma once
#ifndef Matrix_H
#define Matrix_H
#include <vector>
#include <memory>

using namespace std;

class Matrix {
public:
	Matrix(int length, int width);
	Matrix(int length);
	Matrix(vector<double> vect);
	Matrix();
	Matrix(const Matrix &m);
	int length() const { return l; }
	int width() const { return w; }
	//operators 
	double operator () (const int l, const int w) const;
	void set(const int l, const int w, const double v) const;
	void set(const int &lOffset, const int &wOffset, const Matrix &m) const;
	void Matrix::set(const int lOffset, const Matrix &m) const;
	Matrix clone(const int lOffset, const int wOffset) const;
	Matrix clone(const int lOffset) const;

	void print()const;
	void operator = (const Matrix &m);
	vector<double> getColumn(const int index) const;

	Matrix operator + (const Matrix &m) const;
	Matrix operator - (const Matrix &m) const;
	Matrix operator * (const Matrix &m) const; //Returns dot product
	Matrix x(const Matrix &m) const;
	Matrix operator / (const Matrix &m) const;
	Matrix operator ^ (const Matrix &m) const;

	void operator += (const Matrix &m);
	void operator -= (const Matrix &m);
	void xEqual(const Matrix &m);
	void operator /= (const Matrix &m);
	void operator ^= (const Matrix &m);

	Matrix operator + (const double &v)const;
	Matrix operator - (const double &v)const;
	Matrix operator * (const double &v)const;
	Matrix operator / (const double &v)const;
	Matrix operator ^ (const double &v)const;

	bool Matrix::operator == (const Matrix &m)const;

	void operator += (const double &v)const;
	void operator -= (const double &v)const;
	void operator *= (const double &v)const;
	void operator /= (const double &v)const;
	void operator ^= (const double &v)const;

	bool isColumnVector();
	bool isRowVector();
	Matrix transpose();
	Matrix T();

private:
	int l;
	int w;
	int n;

	vector<unique_ptr<double>> &matrix = vector<unique_ptr<double>>(0);
	void initialize();
	int index(int length, int width)const;
};
#endif