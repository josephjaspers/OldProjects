// Matrix.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Matrix.h"
#include<vector>
#include <iostream>

using namespace std;

Matrix::Matrix(int length, int width)
{

	l = length;
	w = width;
	n = l*w;
	initialize();
}

Matrix::Matrix(int length)
{
	l = length;
	w = 1;
	n = length;
	initialize();
}

Matrix::Matrix(vector<double> vect)
{
	l = vect.size();
	w = 1;
	n = l;
	initialize();

	for (int i = 0; i < vect.size(); ++i) {
		*matrix[i] = vect[i];
	}
}

Matrix::Matrix() : l(l), w(w), n(n)
{
	l = 3;
	w = 3;
	n = 9;
	initialize();
}

Matrix::Matrix(const Matrix & m)
{
	l = m.l;
	w = m.w;
	n = l*w;
	initialize();
	for (int i = 0; i < n; ++i) {
		*matrix[i] = *new double(*m.matrix[i]);
	}
}

double Matrix::operator()(const int length, const int width)const
{
	return *matrix[length * w + width];
}

void Matrix::set(const int l, const  int w, const  double v)const
{
	cout << matrix.size() << "matrix size " << endl;
	cout << " the location is " << (l * width() + w) << endl;

	*matrix[index(l, w)] = v;
}
void Matrix::set(const int lOffset, const  Matrix &m)const {
	set(lOffset, 0, m);
}
Matrix Matrix::clone(const int lOffset, const  int wOffset)const
{
	if (l - lOffset < 0 || w - wOffset < 0 || lOffset < 0 || wOffset < 0) {
		throw exception("out of range bounds");
	}
	Matrix m(l - lOffset, w - wOffset);
	for (int l = lOffset; l < length(); ++l) {
		for (int w = wOffset; w < width(); ++w) {
			*m.matrix[index(l - lOffset, w - wOffset)] = *new double(*matrix[index(l, w)]);
		}
	}
	return m;
}
Matrix Matrix::clone(const int lOffset)const
{
	return clone(lOffset, 0);
}
void Matrix::print()const
{
	cout.precision(2);
	for (int l1 = 0; l1 < l; ++l1) {
		for (int w1 = 0; w1 < w; ++w1) {
			cout << fixed << *matrix[index(l1, w1)] << " ";
		}
		cout << endl;
	}
}

void Matrix::operator=(const Matrix &m)
{
	matrix.clear();
	l = m.l;
	w = m.w;
	n = l*w;
	for (int i = 0; i < m.matrix.size(); ++i) {
		matrix.push_back(m.matrix[i]);
	}
}

vector<double> Matrix::getColumn(const int ix)const
{
	vector<double> vect(0);
	for (int l = 0; l < length(); ++l) {
		vect[l] = *matrix[index(l, w)];
	}
	return vect;
}

void Matrix::initialize() {
	for (int i = 0; i < n; ++i) {
		matrix.push_back(0);
	}
}

Matrix Matrix::operator + (const Matrix &m)const {
	if (w != m.w || l != m.l) {
		throw exception("length / width mismatch");
	}

	Matrix mat(l, w);
	for (int l = 0; l < length(); ++l) {
		for (int w = 0; w < width(); ++w) {
			mat.set(l, w, *matrix[index(l, w)] + m(l, w));
		}
	}
	return mat;
}
Matrix Matrix::operator - (const Matrix &m)const {
	if (w != m.w || l != m.l) {
		throw exception("length / width mismatch");
	}

	Matrix mat(l, w);
	for (int l = 0; l < length(); ++l) {
		for (int w = 0; w < width(); ++w) {
			mat.set(l, w, *matrix[index(l, w)] - m(l, w));
		}
	}
	return mat;
}
Matrix Matrix::operator * (const Matrix &m)const {
	if (width() != m.length()) {
		throw  range_error("Dot Product length/width mismatch");
	}
	Matrix mat(l, m.w);

	double tmp;
	for (int l = 0; l < length(); ++l) {
		for (int w = 0; w < m.width(); ++w) {
			tmp = 0;
			for (int l2 = 0; l2 < m.length(); ++l2) {
				tmp += *matrix[index(l, l2)] * m(l2, w);
			}
			mat.set(l, w, tmp);
		}
	}
	return mat;
}
Matrix Matrix::x(const Matrix &m)const {
	if (w != m.w || l != m.l) {
		throw exception("length / width mismatch");
	}

	Matrix mat(l, w);
	for (int l = 0; l < length(); ++l) {
		for (int w = 0; w < width(); ++w) {
			mat.set(l, w, *matrix[index(l, w)] * m(l, w));
		}
	}
	return mat;
} //return multiply
Matrix Matrix::operator / (const Matrix &m)const {
	if (w != m.w || l != m.l) {
		throw exception("length / width mismatch");
	}

	Matrix mat(l, w);
	for (int l = 0; l < length(); ++l) {
		for (int w = 0; w < width(); ++w) {
			mat.set(l, w, *matrix[index(l, w)] / m(l, w));
		}
	}
	return mat;
}
Matrix Matrix::operator ^ (const Matrix &m)const {
	if (w != m.w || l != m.l) {
		throw exception("length / width mismatch");
	}

	Matrix mat(l, w);
	for (int l = 0; l < length(); ++l) {
		for (int w = 0; w < width(); ++w) {
			mat.set(l, w, pow(*matrix[index(l, w)], m(l, w)));
		}
	}
	return mat;
}

bool Matrix::operator == (const Matrix &m)const {
	if (length() != m.length() || width() != m.width()) {
		return false;
	}
	for (int l = 0; l < length(); ++l) {
		for (int w = 0; w < width(); ++w) {
			if (*matrix[index(l, w)] != m(l, w)) {
				return false;
			}
		}
	}
	return true;
}

void Matrix::operator ^= (const Matrix &m) {
	if (l != m.l || w != m.w) {
		throw  range_error("length / width mismatch");
	}

	for (int l = 0; l < length(); ++l) {
		for (int w = 0; w < width(); ++w) {
			set(l, w, (std::pow(*matrix[index(l, w)], m(l, w))));
		}
	}
}
/*
void Matrix::operator *= (Matrix m) {
if (width() != m.length()) {
throw  range_error("Dot Product length/width mismatch");
}
vector<vector<double>> mat;
double tmp;
for (int l = 0; l < length(); ++l) {
for (int w = 0; w < m.width(); ++w) {
tmp = 0;
for (int l2 = 0; l2 < m.length(); ++l2) {
tmp += Matrix[l][l2] * m[l2][w];
}
mat[l][w] = tmp;
}
}
Matrix = mat;
}//dotproduct equal
*/
void Matrix::xEqual(const Matrix &m) {
	if (l != m.l || w != m.w) {
		throw  range_error("length / width mismatch");
	}

	for (int l = 0; l < length(); ++l) {
		for (int w = 0; w < width(); ++w) {
			set(l, w, (pow(*matrix[index(l, w)], m(l, w))));
		}
	}
}//multiply equal
void Matrix::operator /= (const Matrix &m) {
	if (l != m.l || w != m.w) {
		throw  range_error("length / width mismatch");
	}

	for (int l = 0; l < length(); ++l) {
		for (int w = 0; w < width(); ++w) {
			set(l, w, (*matrix[index(l, w)] / m(l, w)));
		}
	}
}
void Matrix::operator += (const Matrix &m) {
	if (l != m.l || w != m.w) {
		throw  range_error("length / width mismatch");
	}

	for (int l = 0; l < length(); ++l) {
		for (int w = 0; w < width(); ++w) {
			set(l, w, (*matrix[index(l, w)] + m(l, w)));
		}
	}
}
void Matrix::operator -= (const Matrix &m) {
	if (l != m.l || w != m.w) {
		throw  range_error("length / width mismatch");
	}

	for (int l = 0; l < length(); ++l) {
		for (int w = 0; w < width(); ++w) {
			set(l, w, (*matrix[index(l, w)] - m(l, w)));
		}
	}
}

Matrix Matrix::operator + (const double &v)const {
	Matrix mat(l, w);
	for (int l = 0; l < length(); ++l) {
		for (int w = 0; w < width(); ++w) {
			mat.set(l, w, *matrix[index(l, w)] + v);
		}
	}
	return mat;
}
Matrix Matrix::operator - (const double &v)const {
	Matrix mat(l, w);
	for (int l = 0; l < length(); ++l) {
		for (int w = 0; w < width(); ++w) {
			mat.set(l, w, *matrix[index(l, w)] - v);
		}
	}
	return mat;
}
Matrix Matrix::operator * (const double &v)const {
	Matrix mat(l, w);
	for (int l = 0; l < length(); ++l) {
		for (int w = 0; w < width(); ++w) {
			mat.set(l, w, *matrix[index(l, w)] * v);
		}
	}
	return mat;
}
Matrix Matrix::operator / (const double &v)const {
	Matrix mat(l, w);
	for (int l = 0; l < length(); ++l) {
		for (int w = 0; w < width(); ++w) {
			mat.set(l, w, *matrix[index(l, w)] / v);
		}
	}
	return mat;
}
Matrix Matrix::operator ^ (const double &v)const {
	Matrix mat(l, w);
	for (int l = 0; l < length(); ++l) {
		for (int w = 0; w < width(); ++w) {
			mat.set(l, w, pow(*matrix[index(l, w)], v));
		}
	}
	return mat;
}

void Matrix::operator += (const double &v)const {
	for (int l = 0; l < length(); ++l) {
		for (int w = 0; w < width(); ++w) {
			set(l, w, *matrix[index(l, w)] + v);
		}
	}
}
void Matrix::operator -= (const double &v)const {
	for (int l = 0; l < length(); ++l) {
		for (int w = 0; w < width(); ++w) {
			set(l, w, *matrix[index(l, w)] - v);
		}
	}
}
void Matrix::operator *= (const double &v)const {
	for (int l = 0; l < length(); ++l) {
		for (int w = 0; w < width(); ++w) {
			set(l, w, *matrix[index(l, w)] * v);
		}
	}
}
void Matrix::operator /= (const double &v)const {
	for (int l = 0; l < length(); ++l) {
		for (int w = 0; w < width(); ++w) {
			set(l, w, *matrix[index(l, w)] / v);
		}
	}
}
void Matrix::operator ^= (const double &v)const {
	for (int l = 0; l < length(); ++l) {
		for (int w = 0; w < width(); ++w) {
			set(l, w, pow(*matrix[index(l, w)], v));
		}
	}
}

Matrix Matrix::transpose() {
	Matrix m(w, l);
	for (int l = 0; l < length(); ++l) {
		for (int w = 0; w < width(); ++w) {
			m.set(w, l, *matrix[index(l, w)]);
		}
	}
	return m;
}
Matrix Matrix::T() {
	return transpose();
}

bool Matrix::isColumnVector() {
	return w == 1;
}
bool Matrix::isRowVector()
{
	return l == 1;
}
int Matrix::index(int length, int width)const
{
	if (length < 0 || width < 0 || length >= l || width >= w) {
		throw exception("out of bounds");
	}
	return (length * w + width);
}
/*
int main() {
cout << "Main method - Matrix test class" << endl;
Matrix x = Matrix(2, 3);
cout << "initialized x" << endl;
x.set(0, 0, 1);
x.set(0, 1, 2);
x.set(0, 2, 3);
x.set(1, 0, 4);
x.set(1, 1, 5);
x.set(1, 2, 6);


x.print();

cout << "initialized y" << endl;
Matrix y = Matrix(3, 2);
y.set(0, 0, 7);
y.set(0, 1, 8);
y.set(1, 0, 9);
y.set(1, 1, 10);
y.set(2, 0, 11);
y.set(2, 1, 12);

y.print();

Matrix xy = x * y;
cout << "xy " << endl;
xy.print();

cout << " yT - x" << endl;
xy = y.T() - x;
xy.print();
int a;
cin >> a;
}
*/