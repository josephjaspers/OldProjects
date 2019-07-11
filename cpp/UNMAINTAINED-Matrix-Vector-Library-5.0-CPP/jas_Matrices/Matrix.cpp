#include "Matrix.h"

Matrix::Matrix()
{
	x = 0;
	y = 0;
	n = 0;

	initialized = false;
}

Matrix::Matrix(unsigned int length, unsigned int width)
{
	y = length;
	x = width;
	n = length * width;

	initialize();
}

Matrix::Matrix(const std::vector<std::vector<double>>& m)
{
	y = m.size();
	x = m[0].size();
	n = x * y;

	initialize();

	int index = 0;
	for (int i = 0; i < m.size(); ++i) {
		for (int j = 0; j < m[0].size(); ++j) {
			matrix[index] = m[i][j];
			++index;
		}
	}
}

Matrix::Matrix(std::vector<double> mat, int length, int width)
{
	y = length;
	x = width;
	n = x * y;

	initialize();

	for (int i = 0; i < mat.size(); ++i) {
		matrix[i] = mat[i];
	}
}

Matrix::Matrix(const Matrix & cpy)
{
	if (!(cpy.initialized)) {
		x = 0;
		y = 0;
		n = 0;
		initialized = false;
		return;
	}

	x = cpy.x;
	y = cpy.y;
	n = cpy.n;

	initialize();

	copy(matrix, cpy.matrix, n);
}

Matrix::~Matrix()
{
	if (initialized) {
		delete[] matrix;
	}
}

bool Matrix::isInitialized() const
{
	return initialized;
}


int Matrix::length() const
{
	return x;
}

int Matrix::width() const
{
	return y;
}

int Matrix::size() const
{
	return n;
}

Matrix & Matrix::operator=(const Matrix & m)
{
	if (initialized) {
		chkBounds(m);
		copy(matrix, m.matrix, n);
	} else {
	x = m.x;
	y = m.y;
	n = m.n;

	initialize();
	copy(matrix, m.matrix, n);
	}
	return *this;
}

Matrix & Matrix::copy_elements(const Matrix & m)
{
	chkBounds(m);
	if (!initialized) {
		x = m.x;
		y = m.y;
		n = x * y;
		initialize();
	}
	else if (n != m.n) {
		std::cout << "copy_elements must be of same size (accepts different dimensions)" << std::endl;
	}
	copy(matrix, m.matrix, n);
	return *this;
}

bool Matrix::operator==(const Matrix & m) const
{
	if (length() != m.length() || width() != m.width()) {
		return false;
	}
	return equal(matrix, m.matrix, n);
}

double & Matrix::operator[](int length)
{
	return matrix[length];
}

Matrix Matrix::operator*(const Matrix & m) const
{
	dot_chkBounds(m);
	Matrix r = Matrix(y, m.x);
	Matrix_Operations::fill(r.matrix, 0, r.size());
	dot(r.matrix, matrix, x, y, m.matrix, m.x, m.y);
	return r;
}

Matrix Matrix::operator->*(const Matrix & m) const
{
	dot_transpose_chkBounds(m);
	Matrix r = Matrix(x, m.x);
	Matrix_Operations::fill(r.matrix, 0, r.size());
	dot_transpose(r.matrix, matrix, x, y, m.matrix, m.x, m.y);
	return r;
}

Matrix Matrix::operator^(const Matrix & m) const
{
	chkBounds(m);
	Matrix r = Matrix(y, x);
	Matrix_Operations::power(r.matrix, matrix, m.matrix, n);

	return r;
}

Matrix Matrix::operator/(const Matrix & m) const
{
	chkBounds(m);
	Matrix r = Matrix(y, x);
	divide(r.matrix, matrix, m.matrix, n);

	return r;
}

Matrix Matrix::operator+(const Matrix & m) const
{
	chkBounds(m);
	Matrix r = Matrix(y, x);
	add(r.matrix, matrix, m.matrix, n);
	return r;
}

Matrix Matrix::operator-(const Matrix & m) const
{
	chkBounds(m);
	Matrix r = Matrix(y, x);
	subtract(r.matrix, matrix, m.matrix, n);
	return r;
}

Matrix Matrix::operator&(const Matrix & m) const
{
	chkBounds(m);
	Matrix r = Matrix(y, x);
	multiply(r.matrix, matrix, m.matrix, n);
	return r;
}

Matrix & Matrix::operator^=(const Matrix & m)
{
	chkBounds(m);
	power(matrix, matrix, m.matrix, n);
	return *this;
}

Matrix & Matrix::operator/=(const Matrix & m)
{
	chkBounds(m);
	divide(matrix, matrix, m.matrix, n);
	return *this;
}

Matrix & Matrix::operator+=(const Matrix & m)
{
	chkBounds(m);
	add(matrix, matrix, m.matrix, n);
	return *this;
}

Matrix & Matrix::operator-=(const Matrix & m)
{
	chkBounds(m);
	subtract(matrix, matrix, m.matrix, n);
	return *this;
}

Matrix & Matrix::operator&=(const Matrix & m)
{
	chkBounds(m);
	multiply(matrix, matrix, m.matrix, n);
	return *this;
}

Matrix Matrix::operator^(const double & d) const
{
	Matrix r = Matrix(y, x);
	power(r.matrix, matrix, d, n);
	return r;
}

Matrix Matrix::operator/(const double & d) const
{
	Matrix r = Matrix(y, x);
	divide(r.matrix, matrix, d, n);
	return r;
}

Matrix Matrix::operator+(const double & d) const
{
	Matrix r = Matrix(y, x);
	add(r.matrix, matrix, d, n);
	return r;
}

Matrix Matrix::operator-(const double & d) const
{
	Matrix r = Matrix(y, x);
	subtract(r.matrix, matrix, d, n);
	return r;
}

Matrix Matrix::operator&(const double & d) const
{
	Matrix r = Matrix(y, x);
	multiply(r.matrix, matrix, d, n);
	return r;
}

Matrix& Matrix::operator^=(const double & d)
{
	power(matrix, matrix, d, n);
	return *this;
}

Matrix& Matrix::operator/=(const double & d)
{
	divide(matrix, matrix, d, n);
	return *this;
}

Matrix& Matrix::operator+=(const double & d)
{
	add(matrix, matrix, d, n);
	return *this;
}

Matrix& Matrix::operator-=(const double & d)
{
	subtract(matrix, matrix, d, n);
	return *this;
}

Matrix& Matrix::operator&=(const double & d)
{
	multiply(matrix, matrix, d, n);
	return *this;
}

double Matrix::max() const
{
	double max = 0;
	max_val(matrix, &max, n);
	return max;
}

double Matrix::min() const
{
	double min = 0;
	min_val(matrix, &min, n);
	return min;
}

double Matrix::max_id(int & x, int & y)
{
	int index = 0;
	double max = 0;
	max_index(matrix, &max, &index, n);
	x = index % length();
	y = (index - x) * width();
	return max;

}

double Matrix::min_id(int & x, int & y)
{
	int index = 0;
	double max = 0;
	max_index(matrix, &max, &index, n);
	x = index % length();
	y = floor(index / length());
	return max;
}

double Matrix::max_id(int & i)
{
	double max = 0;
	max_index(matrix, &max, &i, n);
	return max;
}

double Matrix::min_id(int & i)
{
	double min;
	min_index(matrix, &min, &i, n);
	return min;
}

Matrix& Matrix::fill(double v)
{
	Matrix_Operations::fill(matrix, v, n);
	return *this;
}

void Matrix::fill(Matrix & m, double v)
{
	m.fill(v);
}

bool Matrix::isColumnVector() const
{
	return x == 1;
}

bool Matrix::isRowVector() const
{
	return y == 1;
}

Matrix Matrix::transpose() const
{
	Matrix trans = Matrix(x, y);
	Matrix_Operations::transpose(trans.matrix, matrix, x, y);
	return trans;
}

Matrix Matrix::T() const
{
	return transpose();
}

void Matrix::print() const
{
	for (int i = 0; i < n; ++i) {
		if (i % x == 0)
			std::cout << std::endl;

		std::cout << matrix[i] << " ";
	}
	std::cout << std::endl;
}

void Matrix::print(int p) const
{
	std::cout.precision(p);
	print();
}

Matrix Matrix::read(std::ifstream & f)
{
	bool initialized;
	f >> initialized;
	if (!initialized) {
		return Matrix();
	}
	int x, y, n;
	f >> x;
	f >> y;
	f >> n;

	Matrix r = Matrix(y, x);
	for (int i = 0; i < n; ++i) {
		double read_value;
		f >> read_value;

		r.matrix[i] = read_value;
	}

	return r;
}

void Matrix::write(std::ofstream & o)
{
	o << initialized << ' ';
	if (!initialized) {
		return;
	}

	o << x << ' ';
	o << y << ' ';
	o << n << ' ';

	for (int i = 0; i < n; ++i) {
		o << matrix[i] << ' ';
	}
}

const double & Matrix::get(int x, int y) const
{
	return matrix[y * this->x + x];
}

void Matrix::printDim() const
{
	std::cout << "[" << x << "]" << "[" << y << "]" << std::endl;
}

double * Matrix::getInternals()
{
	return matrix;
}

const double * Matrix::getInternals_const() const
{
	return matrix;
}

void Matrix::initialize()
{
	matrix = new double[n];
	initialized = true;
}

void Matrix::chkBounds(const Matrix & m) const
{
	if (x != m.x || y != m.y) {
		std::cout << " length width mismatch [x,y] *this [" << x << "," << y << "] param@ [" << m.x << "," << m.y << "]" << std::endl;
		throw std::invalid_argument("invalid");
	}
}

void Matrix::dot_chkBounds(const Matrix & m) const
{
	if (x != m.y) {
		std::cout << " dot product mismatch " << std::endl;
		std::cout << "this x = " << x << " param y = " << m.y << std::endl;
		throw std::invalid_argument("error");
	}
}

void Matrix::dot_transpose_chkBounds(const Matrix & m) const
{
	if (x != m.x) {
		std::cout << " dot product mismatch " << std::endl;
		std::cout << "this x = " << x << " param y = " << m.y << std::endl;
		throw std::invalid_argument("error");
	}
}

void Matrix::chkBounds(int x, int y) const
{
	if (x < 0 || y < 0) {
		std::cout << " index value below 0 [" << x << "," << y << "]" << std::endl;
		throw std::invalid_argument("error");
	}
}
