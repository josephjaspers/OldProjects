#include "Vector.h"

Vector::Vector()
{
	x = 0;
	y = 0;
	n = 0;

	initialized = false;
}

Vector::Vector(unsigned int width)
{
	x = 1;
	y = width;
	n = x * y;
	initialize();
}

Vector::Vector(const Vector & cpy)
{
	if (cpy.isInitialized()) {
		x = cpy.x;
		y = cpy.y;
		n = cpy.n;

		initialize();

		copy(vector, cpy.vector, n);
	}
	else {
		x = 0;
		y = 0;
		n = 0;
		initialized = false;
	}
}

Vector::Vector(std::vector<double> v)
{
	y = v.size();
	x = 1;
	n = y;
	initialize();

	for (int i = 0; i < n; ++i) {
		vector[i] = v[i];
	}
}

Vector::~Vector()
{
	if (initialized) {
		delete[] vector;
	}
}

bool Vector::isInitialized() const
{
	return initialized;
}


int Vector::length() const
{
	return x;
}

int Vector::width() const
{
	return y;
}

int Vector::size() const
{
	return n;
}

Vector & Vector::operator=(const Vector & m)
{
	if (initialized) {
		chkBounds(m);
		copy(vector, m.vector, n);
	} else {
	x = m.x;
	y = m.y;
	n = m.n;

	initialize();
	copy(vector, m.vector, n);
	}
	return *this;
}

bool Vector::operator==(const Vector & m) const
{
	if (length() != m.length() || width() != m.width()) {
		return false;
	}
	return equal(vector, m.vector, n);
}

double & Vector::operator[](int length)
{
	return vector[length];
}


Matrix Vector::operator->*(const Vector & m) const
{
	//Technically your transposing the second Vector
	dot_transpose_chkBounds(m);
	Matrix r = Matrix(y, m.y);
	Matrix_Operations::fill(r.matrix, 0, r.size());
	dot(r.matrix, vector, x, y, m.vector, m.y, m.x);
	return r;
}

double Vector::operator*(const Vector & v) const
{
	chkBounds(v);
	Vector r = Vector(y);
	double out = 0;
	dot_inner(out, vector, v.vector, n);
	return out;
}

double Vector::operator*(const double & d) const
{
	double out = 0;
	dot(&out, vector, d, n);
	return out;
}

Vector Vector::operator^(const Vector & m) const
{
	chkBounds(m);
	Vector r = Vector(n);
	Matrix_Operations::power(r.vector, vector, m.vector, n);

	return r;
}

Vector Vector::operator/(const Vector & m) const
{
	chkBounds(m);
	Vector r = Vector(n);
	divide(r.vector, vector, m.vector, n);

	return r;
}

Vector Vector::operator+(const Vector & m) const
{
	chkBounds(m);
	Vector r = Vector(n);
	add(r.vector, vector, m.vector, n);
	return r;
}

Vector Vector::operator-(const Vector & m) const
{
	chkBounds(m);
	Vector r = Vector(n);
	subtract(r.vector, vector, m.vector, n);
	return r;
}

Vector Vector::operator&(const Vector & m) const
{
	chkBounds(m);
	Vector r = Vector(n);
	multiply(r.vector, vector, m.vector, n);
	return r;
}

Vector & Vector::operator^=(const Vector & m)
{
	chkBounds(m);
	power(vector, vector, m.vector, n);
	return *this;
}

Vector & Vector::operator/=(const Vector & m)
{
	chkBounds(m);
	divide(vector, vector, m.vector, n);
	return *this;
}

Vector & Vector::operator+=(const Vector & m)
{
	chkBounds(m);
	add(vector, vector, m.vector, n);
	return *this;
}

Vector & Vector::operator-=(const Vector & m)
{
	chkBounds(m);
	subtract(vector, vector, m.vector, n);
	return *this;
}

Vector & Vector::operator&=(const Vector & m)
{
	chkBounds(m);
	multiply(vector, vector, m.vector, n);
	return *this;
}

Vector Vector::operator^(const double & d) const
{
	Vector r = Vector(n);
	power(r.vector, vector, d, n);
	return r;
}

Vector Vector::operator/(const double & d) const
{
	Vector r = Vector(n);
	divide(r.vector, vector, d, n);
	return r;
}

Vector Vector::operator+(const double & d) const
{
	Vector r = Vector(n);
	add(r.vector, vector, d, n);
	return r;
}

Vector Vector::operator-(const double & d) const
{
	Vector r = Vector(n);
	subtract(r.vector, vector, d, n);
	return r;
}

Vector Vector::operator&(const double & d) const
{
	Vector r = Vector(n);
	multiply(r.vector, vector, d, n);
	return r;
}

Vector& Vector::operator^=(const double & d)
{
	power(vector, vector, d, n);
	return *this;
}

Vector& Vector::operator/=(const double & d)
{
	divide(vector, vector, d, n);
	return *this;
}

Vector& Vector::operator+=(const double & d)
{
	add(vector, vector, d, n);
	return *this;
}

Vector& Vector::operator-=(const double & d)
{
	subtract(vector, vector, d, n);
	return *this;
}

Vector& Vector::operator&=(const double & d)
{
	multiply(vector, vector, d, n);
	return *this;
}

double Vector::max() const
{
	double max = 0;
	max_val(vector, &max, n);
	return max;
}

double Vector::min() const
{
	double min = 0;
	min_val(vector, &min, n);
	return min;
}

double Vector::max_id(int & x, int & y)
{
	int index = 0;
	double max = 0;
	max_index(vector, &max, &index, n);
	x = index % length();
	y = (index - x) * width();
	return max;

}

double Vector::min_id(int & x, int & y)
{
	int index = 0;
	double max = 0;
	max_index(vector, &max, &index, n);
	x = index % length();
	y = floor(index / length());
	return max;
}

double Vector::max_id(int & i)
{
	double max = 0;
	max_index(vector, &max, &i, n);
	return max;
}

double Vector::min_id(int & i)
{
	double min;
	min_index(vector, &min, &i, n);
	return min;
}

Vector& Vector::fill(double v)
{
	Matrix_Operations::fill(vector, v, n);
	return *this;
}

void Vector::fill(Vector & m, double v)
{
	m.fill(v);
}

void Vector::print() const
{
	for (int i = 0; i < n; ++i) {
		std::cout << vector[i] << " ";
	}
	//std::cout << std::endl;
}

void Vector::print(int p) const
{
	std::cout.precision(p);
	print();
}

Vector Vector::read(std::ifstream & f)
{
	bool initialized;
	f >> initialized;
	if (!initialized) {
		return Vector();
	}
	int x, y, n;
	f >> x;
	f >> y;
	f >> n;

	Vector r = Vector(y);
	for (int i = 0; i < n; ++i) {
		double read_value;
		f >> read_value;

		r.vector[i] = read_value;
	}

	return r;
}

void Vector::write(std::ofstream & o)
{
	o << initialized << ' ';
	if (!initialized) {
		return;
	}

	o << x << ' ';
	o << y << ' ';
	o << n << ' ';

	for (int i = 0; i < n; ++i) {
		o << vector[i] << ' ';
	}
}

void Vector::initialize()
{
	vector = new double[n];
	initialized = true;
}

void Vector::chkBounds(const Vector & m) const
{
	if (x != m.x || y != m.y) {
		std::cout << " length width mismatch [x,y] *this [" << x << "," << y << "] param@ [" << m.x << "," << m.y << "]" << std::endl;
		throw std::invalid_argument("invalid");
	}
}

void Vector::dot_chkBounds(const Vector & m) const
{
	if (x != m.y) {
		std::cout << " dot product mismatch " << std::endl;
		std::cout << "this x = " << x << " param y = " << m.y << std::endl;
		throw std::invalid_argument("error");
	}
}

void Vector::dot_transpose_chkBounds(const Vector & m) const
{
	if (x != m.x) {
		std::cout << " dot product mismatch " << std::endl;
		std::cout << "this x = " << x << " param y = " << m.y << std::endl;
		throw std::invalid_argument("error");
	}
}

void Vector::chkBounds(int x, int y) const
{
	if (x < 0 || y < 0) {
		std::cout << " index value below 0 [" << x << "," << y << "]" << std::endl;
		throw std::invalid_argument("error");
	}
}
Vector Matrix::operator*(const Vector & v) const
{
	if (x != v.y) {
		std::cout << " m.x != v.y" << std::endl;
		printDim();
		std::cout << " vector y " << v.y << "vector x " << v.x << std::endl;
		throw std::invalid_argument("err");
	}
	Vector r = Vector(y); //width of matrix
	Matrix_Operations::fill(r.vector, 0, r.size());
	dot(r.vector, matrix, x, y, v.vector, v.x, v.y);
	return r;
}
Vector Matrix::operator->* (const Vector & v) const {
	std::cout << " ->* (Matrix by Vector  not working " << std::endl;
	
	if (y != v.y) {
		std::cout << " m.width != v.length" << std::endl;
		throw std::invalid_argument("err");
	}
	Vector r = Vector(x); //width of matrix
	Matrix_Operations::fill(r.vector, 0, x);
	
	//std::cout << "X slength is " << x << std::endl;
	dot_transpose(r.vector, matrix, x, y, v.vector, v.x, v.y);
	return r;
}
