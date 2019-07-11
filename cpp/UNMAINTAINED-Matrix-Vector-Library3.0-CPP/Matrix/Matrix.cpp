#include "stdafx.h"
#include "Matrix.h"

Matrix::Matrix() {
	l = -1;
	w = -1;
	n = -1;
	initialized = false;
}
Matrix::Matrix(unsigned int length, unsigned int width) {
	if (length < 0 || width < 0) {
		cout << " length width must be > 0 || length = " << length << " width = " << width << endl;
		throw out_of_range("Error");
	 }
	l = length;
	w = width;
	n = length * width;

	initialize();
	initialized = true;
}
Matrix::Matrix(const vector<vector<double>>& m)
{
	l = m.size();
	w = m[0].size();
	n = l * w;

	initialize();
	for (int i = 0; i < l; ++i) {
		for (int j = 0; j < w; ++i) {
			theMatrix[i][j] = m[i][j];
		}
	}
}
Matrix::Matrix(const Matrix & cpy)
{
	if (cpy.initialized) {
		l = cpy.l;
		w = cpy.w;
		n = cpy.n;
		initialize();
		for (int x = 0; x < l; ++x) {
			for (int y = 0; y < w; ++y) {
				theMatrix[x][y] = cpy.theMatrix[x][y];
			}
		}
	}
	else {
		l = -1;
		w = -1;
		n = -1;
		initialized = false;
	}
}
Matrix::~Matrix()
{
	if (initialized){
	for (int x = 0; x < l; ++x) {
		delete[] theMatrix[x];
	}
	delete[] theMatrix;
	}
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
Matrix& Matrix::operator=(const Matrix& cpy) {
	if (!initialized) {
		if (!cpy.initialized) {
			return *this;
		}
		l = cpy.l;
		w = cpy.w;
		n = l * w;
		initialize();
		initialized = true;
		for (int x = 0; x < l; ++x) {
			for (int y = 0; y < w; ++y) {
				theMatrix[x][y] = cpy.theMatrix[x][y];
			}
		}
	}
	else if (l == cpy.l && w == cpy.w) {
		for (int x = 0; x < l; ++x) {
			for (int y = 0; y < w; ++y) {
				theMatrix[x][y] = cpy.theMatrix[x][y];
			}
		}
	}
	else {
		cout << "copy operator : Matrix is non mutable " << endl;
		cout << "   l = " << l << " w = " << w << " param@ l = " << cpy.l << " w = " << cpy.w << endl;
		throw out_of_range("error");
	}
	return *this;
}
bool Matrix::operator==(const Matrix & m) const {
	if (length() != m.length() || width() != m.width()) {
		return false;
	}
	for (int l = 0; l < length(); ++l) {
		for (int w = 0; w < width(); ++w) {
			if (theMatrix[l][w] == m.theMatrix[l][w]) {
				return false;
			}
		}
	}
	return true;
}
double& Matrix::operator()(int length, int width) {
	chkBounds(length, width);
	return theMatrix[length][width];
}
Matrix Matrix::operator ^ (const Matrix& m) const {
	chkBounds(m);

	Matrix mat = Matrix(l, w);
	for (int l = 0; l < length(); ++l) {
		for (int w = 0; w < width(); ++w) {
			mat(l, w) = pow(theMatrix[l][w], m.theMatrix[l][w]);
		}
	}
	return mat;
}
Matrix Matrix::operator*(const Matrix& m) const {
	if (width() != m.length()) {
		cout << "dotproduct (*) mismatch " << "\n" << " this.width = " << w << " param@ length " << m.l << endl;
		throw range_error("Dot Product length/width mismatch");
	}
	Matrix mat(length(), m.width());

	double tmp;
	for (int l = 0; l < length(); ++l) {
		for (int w = 0; w < m.width(); ++w) {
			tmp = 0;
			for (int l2 = 0; l2 < m.length(); ++l2) {
				tmp += theMatrix[l][l2] * m.theMatrix[l2][w];
			}
			mat(l, w) = tmp;
		}
	}
	return mat;
}
Matrix Matrix::operator/(const Matrix& m) const {
	chkBounds(m);

	Matrix mat = Matrix(l, w);
	for (int l = 0; l < length(); ++l) {
		for (int w = 0; w < width(); ++w) {
			mat(l, w) = theMatrix[l][w] / m.theMatrix[l][w];
		}
	}
	return mat;
}
Matrix Matrix::operator+(const Matrix& m) const {
	chkBounds(m);

	Matrix mat = Matrix(l, w);
	for (int l = 0; l < length(); ++l) {
		for (int w = 0; w < width(); ++w) {
			mat(l, w) = theMatrix[l][w] + m.theMatrix[l][w];
		}
	}
	return mat;
}
Matrix Matrix::operator-(const Matrix& m) const {
	chkBounds(m);

	Matrix mat = Matrix(l, w);
	for (int l = 0; l < length(); ++l) {
		for (int w = 0; w < width(); ++w) {
			mat(l, w) = theMatrix[l][w] - m.theMatrix[l][w];
		}
	}
	return mat;
}
Matrix Matrix::operator&(const Matrix & m) const
{
	chkBounds(m);

	Matrix mat = Matrix(l, w);
	for (int l = 0; l < length(); ++l) {
		for (int w = 0; w < width(); ++w) {
			mat(l, w) = theMatrix[l][w] * m.theMatrix[l][w];
		}
	}
	return mat;
}
Matrix & Matrix::operator^=(const Matrix& m) {
	chkBounds(m);

	for (int l = 0; l < length(); ++l) {
		for (int w = 0; w < width(); ++w) {
			theMatrix[l][w] = pow(theMatrix[l][w], m.theMatrix[l][w]);
		}
	}
	return *this;
}
Matrix Matrix::operator&(const double& d) const
{
	Matrix r = Matrix(l, w);
	for (int x = 0; x < l; ++x) {
		for (int y = 0; y < w; ++y) {
			r(x, y) = theMatrix[x][y] * d;
		}
	}
	return r;
}

Matrix & Matrix::operator^=(const double & d)
{
	for (int x = 0; x < l; ++x) {
		for (int y = 0; y < w; ++y) {
			theMatrix[x][y] = pow(theMatrix[x][y], d);
		}
	}
	return *this;
}

Matrix & Matrix::operator/=(const double & d)
{
	for (int x = 0; x < l; ++x) {
		for (int y = 0; y < w; ++y) {
			theMatrix[x][y] /= d;
		}
	}
	return *this;
}

Matrix & Matrix::operator+=(const double & d)
{
	for (int x = 0; x < l; ++x) {
		for (int y = 0; y < w; ++y) {
			theMatrix[x][y] += d;
		}
	}
	return *this;
}

Matrix & Matrix::operator-=(const double & d)
{
	for (int x = 0; x < l; ++x) {
		for (int y = 0; y < w; ++y) {
			theMatrix[x][y] -= d;
		}
	}
	return *this;
}

Matrix & Matrix::operator&=(const double & d)
{
	for (int x = 0; x < l; ++x) {
		for (int y = 0; y < w; ++y) {
			theMatrix[x][y] *= d;
		}
	}
	return *this;
}
Matrix & Matrix::operator/=(const Matrix& m) {
	chkBounds(m);

	for (int l = 0; l < length(); ++l) {
		for (int w = 0; w < width(); ++w) {
			theMatrix[l][w] /= m.theMatrix[l][w];
		}
	}
	return *this;
}
Matrix & Matrix::operator+=(const Matrix& m) {
	chkBounds(m);

	for (int l = 0; l < length(); ++l) {
		for (int w = 0; w < width(); ++w) {
			theMatrix[l][w] += m.theMatrix[l][w];
		}
	}
	return *this;
}

Matrix & Matrix::operator-=(const Matrix& m) {
	chkBounds(m);

	for (int l = 0; l < length(); ++l) {
		for (int w = 0; w < width(); ++w) {
			theMatrix[l][w] -= m.theMatrix[l][w];
		}
	}
	return *this;
}

Matrix & Matrix::operator&=(const Matrix & m)
{
	chkBounds(m);

	for (int l = 0; l < length(); ++l) {
		for (int w = 0; w < width(); ++w) {
			theMatrix[l][w] *= m.theMatrix[l][w];
		}
	}
	return *this;
}

Matrix Matrix::operator^(const double & d) const
{
	Matrix r = Matrix(l, w);
	for (int x = 0; x < l; ++x) {
		for (int y = 0; y < w; ++y) {
			r(x, y) = pow(theMatrix[x][y], d);
		}
	}
	return r;
}

Matrix Matrix::operator/(const double & d) const
{
	Matrix r = Matrix(l, w);
	for (int x = 0; x < l; ++x) {
		for (int y = 0; y < w; ++y) {
			r(x, y) = theMatrix[x][y] / d;
		}
	}
	return r;
}

Matrix Matrix::operator+(const double & d) const
{
	Matrix r = Matrix(l, w);
	for (int x = 0; x < l; ++x) {
		for (int y = 0; y < w; ++y) {
			r(x, y) = theMatrix[x][y] + d;
		}
	}
	return r;
}

Matrix Matrix::operator-(const double & d) const
{
	Matrix r = Matrix(l, w);
	for (int x = 0; x < l; ++x) {
		for (int y = 0; y < w; ++y) {
			r(x, y) = theMatrix[x][y] - d;
		}
	}
	return r;
}
bool Matrix::isColumnVector() const {
	return width() == 1;
}

bool Matrix::isRowVector() const {
	return length() == 1;
}
Matrix Matrix::transpose() const {
	Matrix m = Matrix(width(), length());

	for (int L = 0; L < length(); ++L) {
		for (int W = 0; W < width(); ++W) {
			m(W, L) = theMatrix[L][W];
		}
	}
	return m;
}
vector<vector<double>> Matrix::getCpyVect() const
{
	return vector<vector<double>>(0);
}
void Matrix::print() const {
	for (int l = 0; l < length(); ++l) {
		for (int w = 0; w < width(); ++w) {
			cout << theMatrix[l][w] << " ";
		}
		cout << endl;
	}
}
void Matrix::print(int p) const {
	cout.precision(p);
	for (int l = 0; l < length(); ++l) {
		for (int w = 0; w < width(); ++w) {
			cout << theMatrix[l][w] << " ";
		}
		cout << endl;
	}
}
void Matrix::deleteMatrix()
{
	for (int x = 0; x < l; ++x) {
		if (theMatrix[x] != nullptr) {
			delete[] theMatrix[x];
		}
	}
	if (theMatrix != nullptr) {
		delete[] theMatrix;
		theMatrix = 0;
	}
}
void Matrix::initialize()
{
	theMatrix = new double*[l];
	for (int i = 0; i < l; ++i) {
		theMatrix[i] = new double[w];
	}
}
void Matrix::chkBounds(const Matrix & m) const
{
	if (l != m.l) {
		cout << " matrix length mismatch" <<
			" this.w = " << w << " param@ w = " << m.w <<
			" this.l = " << l << " param@ l = " << m.l << endl;
		throw out_of_range("error");
	}
	if (w != m.w) {
		cout << " matrix width mismatch" <<
			" this.l = " << l << " param@ l = " << m.l <<
			" this.w = " << w << " param@ w = " << m.w << endl;
		throw out_of_range("error");
	}
}
void Matrix::chkBounds(int x, int y) const
{
	if (x < 0 || x >= l) {
		cout << "out of bounds length - assert! x > 0 || x <= l  :  x = " << x << endl;
		throw out_of_range("error");
	}
	if (y < 0 || y >= w) {
		cout << "out of bounds width - assert! y > 0 || y <= w  :  y = " << y << endl;
		throw out_of_range("error");
	}
}
Matrix Matrix::read(ifstream & f)
{
	bool initialized;
	f >> initialized;
	if (!initialized) {
		return Matrix();
	}
	int l;
	int w;
	int n;
	f >> l;
	f >> w;
	f >> n;

	Matrix m = Matrix(l, w);
	for (int length = 0; length < m.l; ++length) {
		for (int width = 0; width < m.w; ++width) {
			double v;
			f >> v;
			m.theMatrix[length][width] = v;
		}
	}
	return m;
}
void Matrix::write(ofstream & o)
{
	o << initialized << ' ';
	if (!initialized) {
		return;
	}
	o << l;
	o << ' ';
	o << w;
	o << ' ';
	o << n;
	o << ' ';

	for (int l = 0; l < length(); ++l) {
		for (int w = 0; w < width(); ++w) {
			o << theMatrix[l][w] << ' ';
		}
	}
}
const double & Matrix::get(int length, int width) const
{
	if (length < 0 || length >= l || width < 0 || width >= w) {
		throw out_of_range("error");
	}
	return theMatrix[length][width];
}
