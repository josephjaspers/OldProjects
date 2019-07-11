#include "stdafx.h"
#include "Matrix.h"

Matrix::Matrix(unsigned int length, unsigned int width) {
	l = length;
	w = width;
	n = length * width;

	theMatrix = vector<double>(length * width);
}

Matrix::Matrix(const vector<double>& vect) {
	theMatrix = vect;
	l = vect.size();
	w = 1;
	n = l * w;
}

Matrix::Matrix(const vector<vector<double> > & m) {
	l = m.size();
	w = m[0].size();
	n = l * w;

	for (int L = 0; L < m.size(); ++L) {
		if (m[L].size() != w) {
			throw invalid_argument("ragged vector<vector<double>> not applicable");
		}
		for (int W = 0; W < m[L].size(); ++W) {
			theMatrix[index(L, W)] = m[L][W];
		}
	}
}

Matrix::Matrix()
{
	l = 0;
	w = 0;
	n = 0;
	theMatrix = vector<double>(0);
}

Matrix::Matrix(unsigned int length) {
	l = length;
	w = 1;
	n = l;
	theMatrix = vector<double>(l);
}

int Matrix::length() const {
	return l;
}

int Matrix::width() const {
	return w;
}

int Matrix::size() const {
	return n;
}

int Matrix::index(unsigned int length, unsigned int width) const {
	return length * w + width;
}

Matrix::Matrix(const Matrix& m) {
	theMatrix = m.theMatrix;
	Matrix::l = m.l;
	Matrix::w = m.w;
	Matrix::n = m.n;
}

void Matrix::operator=(const Matrix& m) {
	l = m.l;
	w = m.w;
	n = m.n;
	theMatrix = m.theMatrix;
}

bool Matrix::operator==(const Matrix & m) const {
	if (l != m.l || w != m.w) {
		return false;
	}
	for (int i = 0; i < n; ++i) {
		if (theMatrix[i] != m.theMatrix[i]) {
			return false;
		}
	}
	return true;
}

double& Matrix::operator()(int length, int width) {
	return theMatrix[index(length, width)];
}

double& Matrix::operator[](int index) {
	return theMatrix[index];
}

Matrix Matrix::operator ^ (const Matrix& m) const {
	if (l != m.l || w != m.w) {
		throw invalid_argument("length / width mismatch");
	}
	Matrix mat = Matrix(l, w);
	for (int i = 0; i < n; ++i) {
		mat[i] = pow(theMatrix[i], m.theMatrix[i]);
	}
	return mat;
}

Matrix Matrix::operator*(const Matrix& m) const {
	if (w != m.l) {
		throw range_error("Dot Product length/width mismatch");
	}
	Matrix mat(l, m.w);

	double tmp;
	for (int l = 0; l < length(); ++l) {
		for (int w = 0; w < m.width(); ++w) {
			tmp = 0;
			for (int l2 = 0; l2 < m.length(); ++l2) {
				tmp += theMatrix[index(l, l2)] * m.theMatrix[m.index(l2, w)];
			}
			mat(l, w) = tmp;
		}
	}
	return mat;
}

Matrix Matrix::operator/(const Matrix& m) const {
	if (l != m.l || w != m.w) {
		throw invalid_argument("length / width mismatch");
	}
	Matrix mat = Matrix(l, w);
	for (int i = 0; i < n; ++i) {
		mat[i] = theMatrix[i] / m.theMatrix[i];
	}
	return mat;
}

Matrix Matrix::operator+(const Matrix& m) const {
	if (l != m.l || w != m.w) {
		throw invalid_argument("length / width mismatch");
	}
	Matrix mat = Matrix(l, w);
	for (int i = 0; i < n; ++i) {
		mat[i] = theMatrix[i] + m.theMatrix[i];
	}
	return mat;
}

Matrix Matrix::operator-(const Matrix& m) const {
	if (l != m.l || w != m.w) {
		throw invalid_argument("length / width mismatch");
	}
	Matrix mat = Matrix(l, w);
	for (int i = 0; i < n; ++i) {
		mat[i] = theMatrix[i] - m.theMatrix[i];
	}
	return mat;
}

Matrix Matrix::x(const Matrix & m) const
{
	if (l != m.l || w != m.w) {
		throw invalid_argument("length / width mismatch");
	}
	Matrix mat = Matrix(l, w);
	for (int i = 0; i < n; ++i) {
		mat[i] = theMatrix[i] * m.theMatrix[i];
	}
	return mat;
}

void Matrix::operator^=(const Matrix& m) {
	if (l != m.l || w != m.w) {
		throw invalid_argument("length / width mismatch");
	}
	for (int i = 0; i < n; ++i) {
		theMatrix[i] = pow(theMatrix[i], m.theMatrix[i]);
	}
}

void Matrix::operator*=(const Matrix& m) {
	if (l != m.l || w != m.w) {
		throw invalid_argument("length / width mismatch");
	}
	for (int i = 0; i < n; ++i) {
		theMatrix[i] *= m.theMatrix[i];
	}
}

void Matrix::operator/=(const Matrix& m) {
	if (l != m.l || w != m.w) {
		throw invalid_argument("length / width mismatch");
	}
	for (int i = 0; i < n; ++i) {
		theMatrix[i] = theMatrix[i] / m.theMatrix[i];
	}
}

void Matrix::operator+=(const Matrix& m) {
	if (l != m.l || w != m.w) {
		throw invalid_argument("length / width mismatch");
	}
	for (int i = 0; i < n; ++i) {
		theMatrix[i] += m.theMatrix[i];
	}
}

void Matrix::operator-=(const Matrix& m) {
	if (l != m.l || w != m.w) {
		throw invalid_argument("length / width mismatch");
	}
	for (int i = 0; i < n; ++i) {
		theMatrix[i] -= m.theMatrix[i];
	}
}

Matrix Matrix::getColumn(unsigned int col) const {
	Matrix m = Matrix(l);

	for (int W = 0; W < m.n; ++W) {
		m[W] = theMatrix[index(col, W)];
	}
	return m;
}

Matrix Matrix::getRow(unsigned int row) const {
	Matrix m = Matrix(w);

	for (int L = 0; L < m.n; ++L) {
		m[L] = theMatrix[index(L, row)];
	}
	return m;
}

bool Matrix::isColumnVector() const {
	return w == 1;
}

bool Matrix::isRowVector() const {
	return l == 1;
}

Matrix Matrix::transpose() const {
	Matrix m = Matrix(w, l);

	for (int L = 0; L < l; ++L) {
		for (int W = 0; W < w; ++W) {
			m(W, L) = theMatrix[index(L, W)];
		}
	}
	return m;
}

void Matrix::print() const {
	for (int l = 0; l < length(); ++l) {
		for (int w = 0; w < width(); ++w) {
			cout << theMatrix[index(l, w)] << " ";
		}
		cout << endl;
	}
}
void Matrix::print(int p) const {
	cout.precision(p);
	for (int l = 0; l < length(); ++l) {
		for (int w = 0; w < width(); ++w) {
			cout << theMatrix[index(l, w)] << " ";
		}
		cout << endl;
	}
}

Matrix Matrix::cpy() const
{
	return Matrix(*this);
}

Matrix Matrix::cpy(int rowOffset, int columnOffset) const
{
	Matrix m = Matrix(l - rowOffset, w - columnOffset); 
	for (int l = rowOffset; l < length(); ++l) {
		for (int w = columnOffset; w < width(); ++w) {
			m(l- rowOffset, w- columnOffset) = theMatrix[index(l, w)];
		}
	}
	return m;
}

Matrix Matrix::cpy(int rowOffset) const
{
	return cpy(rowOffset, 0);
}
void Matrix::set(unsigned int lOffset, unsigned int wOffset, const Matrix &m) {
	if (l - lOffset != m.l || w - wOffset != m.w) {
		throw exception("l / w mismatch");
	}
	for (int l = lOffset; l < length(); ++l) {
		for (int w = wOffset; w < width(); ++w) {
			theMatrix[index(l, w)] = m.theMatrix[index(l - lOffset, w - wOffset)];
		}
	}
}
void Matrix::set(unsigned int lOffset, const Matrix &m) {
	if (l - lOffset != m.l || w != m.w) {
		cout << "this L/W " << l << "/" << w << "param l/w" << m.length() << "/" << m.width() << endl;
		throw exception("l / w mismatch");
	}
	for (int l = lOffset; l < length(); ++l) {
		for (int w = 0; w < width(); ++w) {
			theMatrix[index(l,w)] = m.theMatrix[index(l - lOffset, w)];
		}
	}
}