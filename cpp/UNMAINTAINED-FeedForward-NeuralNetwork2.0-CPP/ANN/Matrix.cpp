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

Matrix::Matrix(const vector<vector<double>>& m) {
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

Matrix::Matrix(unsigned int length) {
	l = length;
	w = 1;
	n = l;
	theMatrix = vector<double>(l);
}

int Matrix::length() const {
	if (transposed) {
		return w;
	}
	else {
		return l;
	}
}

int Matrix::width() const {
	if (transposed) {
		return l;
	}
	else {
		return w;
	}
}

int Matrix::size() const {
	return n;
}

int Matrix::index(unsigned int length, unsigned int width) const {
	if (!transposed)
		return length * w + width;
	else {
		return width * w + length;
	}
}


Matrix::Matrix(const Matrix& m) {
	theMatrix = m.theMatrix;
	transposed = m.transposed;
	Matrix::l = m.l;
	Matrix::w = m.w;
	Matrix::n = m.n;
}

void Matrix::operator=(const Matrix& m) {
	l = m.l;
	w = m.w;
	n = m.n;
	transposed = m.transposed;
	theMatrix = m.theMatrix;
}

bool Matrix::operator==(const Matrix & m) const {
	if (length() != m.length() || width() != m.width()) {
		return false;
	}
	for (int l = 0; l < length(); ++l) {
		for (int w = 0; w < width(); ++w) {
			if (theMatrix[index(l, w)] != m.theMatrix[index(l, w)]) {
				return false;
			}
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

unique_ptr<Matrix> Matrix::operator ^ (const Matrix& m) const {
	if (length() != m.length() || width() != m.width()) {
		throw invalid_argument("length / width mismatch");
	}
	unique_ptr<Matrix> mat = unique_ptr<Matrix>(new Matrix(l, w));
	for (int l = 0; l < length(); ++l) {
		for (int w = 0; w < width(); ++w) {
			(*mat)(l, w) = pow(theMatrix[index(l, w)], m.theMatrix[index(l, w)]);
		}
	}
	return mat;
}

unique_ptr<Matrix> Matrix::operator*(const Matrix& m) const {
	if (width() != m.length()) {
		throw range_error("Dot Product length/width mismatch");
	}
	unique_ptr<Matrix> mat = unique_ptr<Matrix>(new Matrix(length(), m.width()));

	double tmp;
	for (int l = 0; l < length(); ++l) {
		for (int w = 0; w < m.width(); ++w) {
			tmp = 0;
			for (int l2 = 0; l2 < m.length(); ++l2) {
				tmp += theMatrix[index(l, l2)] * m.theMatrix[m.index(l2, w)];
			}
			(*mat)(l, w) = tmp;
		}
	}
	return mat;
}

unique_ptr<Matrix> Matrix::operator/(const Matrix& m) const {
	if (length() != m.length() || width() != m.width()) {
		throw invalid_argument("length / width mismatch");
	}
	unique_ptr<Matrix> mat = unique_ptr<Matrix>(new Matrix(l, w));
	for (int l = 0; l < length(); ++l) {
		for (int w = 0; w < width(); ++w) {
			(*mat)(l, w) = theMatrix[index(l, w)] / m.theMatrix[index(l, w)];
		}
	}
	return mat;
}

unique_ptr<Matrix> Matrix::operator+(const Matrix& m) const {
	if (length() != m.length() || width() != m.width()) {
		throw invalid_argument("length / width mismatch");
	}
	unique_ptr<Matrix> mat = unique_ptr<Matrix>(new Matrix(l, w));
	for (int l = 0; l < length(); ++l) {
		for (int w = 0; w < width(); ++w) {
			(*mat)(l, w) = theMatrix[index(l, w)] + m.theMatrix[index(l, w)];
		}
	}
	return mat;
}

unique_ptr<Matrix> Matrix::operator-(const Matrix& m) const {
	if (length() != m.length() || width() != m.width()) {
		throw invalid_argument("length / width mismatch");
	}
	unique_ptr<Matrix> mat = unique_ptr<Matrix>(new Matrix(l, w));
	for (int l = 0; l < length(); ++l) {
		for (int w = 0; w < width(); ++w) {
			(*mat)(l, w) = theMatrix[index(l, w)] - m.theMatrix[index(l, w)];
		}
	}
	return mat;
}

unique_ptr<Matrix> Matrix::x(const Matrix & m) const
{
	if (length() != m.length() || width() != m.width()) {
		throw invalid_argument("length / width mismatch");
	}
	unique_ptr<Matrix> mat = unique_ptr<Matrix>(new Matrix(l, w));
	for (int l = 0; l < length(); ++l) {
		for (int w = 0; w < width(); ++w) {
			(*mat)(l, w) = theMatrix[index(l, w)] * m.theMatrix[index(l, w)];
		}
	}
	return mat;
}

Matrix& Matrix::operator^=(const Matrix& m) {
	if (length() != m.length() || width() != m.width()) {
		throw invalid_argument("length / width mismatch");
	}
	for (int l = 0; l < length(); ++l) {
		for (int w = 0; w < width(); ++w) {
			theMatrix[index(l, w)] = pow(theMatrix[index(l, w)], m.theMatrix[index(l, w)]);
		}
	}
	return *this;
}

Matrix& Matrix::operator*=(const Matrix& m) {
	if (length() != m.length() || width() != m.width()) {
		throw invalid_argument("length / width mismatch");
	}
	for (int l = 0; l < length(); ++l) {
		for (int w = 0; w < width(); ++w) {
			theMatrix[index(l, w)] *= m.theMatrix[index(l, w)];
		}
	}
	return *this;
}

Matrix& Matrix::operator/=(const Matrix& m) {
	if (length() != m.length() || width() != m.width()) {
		throw invalid_argument("length / width mismatch");
	}
	for (int l = 0; l < length(); ++l) {
		for (int w = 0; w < width(); ++w) {
			theMatrix[index(l, w)] /= m.theMatrix[index(l, w)];
		}
	}
	return *this;
}

Matrix& Matrix::operator+=(const Matrix& m) {
	if (l != m.l || w != m.w) {
		throw invalid_argument("length / width mismatch");
	}
	for (int i = 0; i < n; ++i) {
		theMatrix[i] += m.theMatrix[i];
	}
	return *this;
}

Matrix& Matrix::operator-=(const Matrix& m) {
	if (length() != m.length() || width() != m.width()) {
		throw invalid_argument("length / width mismatch");
	}
	for (int l = 0; l < length(); ++l) {
		for (int w = 0; w < width(); ++w) {
			theMatrix[index(l, w)] -= m.theMatrix[index(l, w)];
		}
	}
	return *this;
}

unique_ptr<Matrix> Matrix::getColumn(unsigned int col) const {
	unique_ptr<Matrix> m = unique_ptr<Matrix>(new Matrix(l));

	for (int W = 0; W < m->n; ++W) {
		(*m)[W] = theMatrix[index(col, W)];
	}
	return m;
}

unique_ptr<Matrix> Matrix::getRow(unsigned int row) const {
	unique_ptr<Matrix> m = unique_ptr<Matrix>(new Matrix(w));

	for (int L = 0; L < m->n; ++L) {
		(*m)[L] = theMatrix[index(L, row)];
	}
	return m;
}

bool Matrix::isColumnVector() const {
	return width() == 1;
}

bool Matrix::isRowVector() const {
	return length() == 1;
}

unique_ptr<Matrix> Matrix::transpose() const {
	unique_ptr<Matrix> m = unique_ptr<Matrix>(new Matrix(width(), length()));

	for (int L = 0; L < length(); ++L) {
		for (int W = 0; W < width(); ++W) {
			(*m)(W, L) = theMatrix[index(L, W)];
		}
	}
	return m;
}

vector<double> Matrix::getCpyVect() const
{
	return theMatrix;
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

Matrix& Matrix::read(ifstream & f)
{
	f >> l;
	f >> w;
	f >> n;
	f >> transposed;
	theMatrix = vector<double>(0);
	double v;
	for (int i = 0; i < n; ++i) {
		f >> v;
		theMatrix.push_back(v);
	}
	return *this;
}

void Matrix::write(ostream & o)
{
	o << l;
	o << " ";
	o << w;
	o << " ";
	o << n;
	o << " ";
	o << transposed;
	o << " ";
	for (double v : theMatrix) {
		o << v;
		o << " ";
	}
}