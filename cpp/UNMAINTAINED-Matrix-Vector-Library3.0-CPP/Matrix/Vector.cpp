#include "stdafx.h"
#include "Vector.h"

Vector::Vector()
{
	l = -1;
	initialized = false;
}
Vector::Vector(unsigned int length)
{
	theVector = new double[length];
	l = length;
}
Vector::Vector(const vector<double>& vect)
{
	l = vect.size();
	theVector = new double[l];
	for (int i = 0; i < vect.size(); ++i) {
		theVector[i] = vect[i];
	}
}
Vector::Vector(const Vector & v)
{
	if (v.initialized){
		l = v.l;
		theVector = new double[l];
		for (int i = 0; i < l; ++i) {
			theVector[i] = v.theVector[i];
		}
	}
	else {
		l = -1;
		initialized = false;
	}
}
Vector::~Vector()
{
	if (initialized) {
	delete[] theVector;
	theVector = 0;
	}
}
int Vector::length() const
{
	return l;
}
int Vector::width() const
{
	return 1;
}
int Vector::size() const
{
	return l;
}
double & Vector::operator()(int length)
{
	chkBounds(length);
	return theVector[length];
}
double & Vector::operator[](int length)
{
	chkBounds(length);
	return theVector[length];
}
Vector& Vector::operator=(const Vector & v)
{
	if (!initialized) {
		if (!v.initialized) {
			return *this;
		}
		l = v.l;
		theVector = new double[l];
		initialized = true;
		for (int i = 0; i < v.length(); ++i) {
			theVector[i] = v.theVector[i];
		}
	} else if (l == v.l) {
		for (int i = 0; i < l; ++i) {
			theVector[i] = v.theVector[i];
		}
	} else {
		cout << "length mismatch cpy operator = " << endl;
		cout << "Vectors are non mutable : l = " << l << " param@ l = " << v.l << endl;
		throw out_of_range("error");
	}
	return *this;
}
bool Vector::operator==(const Vector & v) const
{
	if (l != v.l) {
		return false;
	}
	for (int i = 0; i < l; ++i) {
		if (theVector[l] != v.theVector[i]) {
			return false;
		}
	}
	return true;
}
Vector Vector::operator^(const Vector & v) const
{
	chkBounds(v);

	Vector r = Vector(l);
	for (int i = 0; i < l; ++i) {
		r(i) = pow(theVector[i], v.theVector[i]);
	}
	return r;
}
Vector Vector::operator/(const Vector & v) const
{
	chkBounds(v);

	Vector r = Vector(l);
	for (int i = 0; i < l; ++i) {
		r(i) = theVector[i] / v.theVector[i];
	}
	return r;
}
Vector Vector::operator+(const Vector & v) const
{
	chkBounds(v);

	Vector r = Vector(l);
	for (int i = 0; i < l; ++i) {
		r(i) = theVector[i] + v.theVector[i];
	}
	return r;
}
Vector Vector::operator-(const Vector & v) const
{
	chkBounds(v);

	Vector r = Vector(l);
	for (int i = 0; i < l; ++i) {
		r(i) = theVector[i] - v.theVector[i];
	}
	return r;
}
Vector Vector::operator&(const Vector & v) const
{
	chkBounds(v);

	Vector r = Vector(l);
	for (int i = 0; i < l; ++i) {
		r(i) = theVector[i] * v.theVector[i];
	}
	return r;
}
Vector& Vector::operator^=(const Vector & v)
{
	chkBounds(v);

	for (int l = 0; l < length(); ++l) {
		theVector[l] = pow(theVector[l], v.theVector[l]);
	}
	return *this;
}
Vector& Vector::operator&=(const Vector & v)
{
	chkBounds(v);

	for (int l = 0; l < length(); ++l) {
		theVector[l] *= v.theVector[l];
	}
	return *this;
}
Vector& Vector::operator/=(const Vector & v)
{
	chkBounds(v);

	for (int l = 0; l < length(); ++l) {
		theVector[l] /= v.theVector[l];
	}
	return *this;
}
Vector& Vector::operator+=(const Vector & v)
{
	chkBounds(v);

	for (int l = 0; l < length(); ++l) {
		theVector[l] += v.theVector[l];
	}
	return *this;
}
Vector& Vector::operator-=(const Vector & v)
{
	for (int l = 0; l < length(); ++l) {
		theVector[l] -= v.theVector[l];
	}
	return *this;
}
Vector Vector::operator^(const double & d) const
{
	Vector r = Vector(l);
	for (int i = 0; i < l; ++i) {
		r[l] = pow(theVector[i], d);
	}
	return r;
}
Vector Vector::operator/(const double & d) const
{
	Vector r = Vector(l);
	for (int i = 0; i < l; ++i) {
		r[i] = theVector[i] / d;
	}
	return r;
}
Vector Vector::operator+(const double & d) const
{
	Vector r = Vector(l);
	for (int i = 0; i < l; ++i) {
		r[i] = theVector[i] + d;
	}
	return r;
}
Vector Vector::operator-(const double & d) const
{
	Vector r = Vector(l);
	for (int i = 0; i < l; ++i) {
		r[i] = theVector[i] - d;
	}
	return r;
}
Vector Vector::operator&(const double & d) const
{
	Vector r = Vector(l);
	for (int i = 0; i < l; ++i) {
		r[i] = theVector[i] * d;
	}
	return r;
}
Vector & Vector::operator^=(const double & d)
{
	for (int i = 0; i < l; ++l) {
		theVector[i] = pow(theVector[i], d);
	}
	return *this;
}
Vector & Vector::operator&=(const double & d)
{
	for (int i = 0; i < l; ++l) {
		theVector[i] *= d;
	}
	return *this;
}
Vector & Vector::operator/=(const double & d)
{
	for (int i = 0; i < l; ++l) {
		theVector[i] /= d;
	}
	return *this;
}
Vector & Vector::operator+=(const double & d)
{
	for (int i = 0; i < l; ++l) {
		theVector[i] += d;
	}
	return *this;
}
Vector & Vector::operator-=(const double & d)
{
	for (int i = 0; i < l; ++l) {
		theVector[i] -= d;
	}
	return *this;
}
vector<double> Vector::getCpyVect() const
{
	vector<double> v = vector<double>(l);
	for (int i = 0; i < l; ++i) {
		v[i] = theVector[i];
	}
	return v;
}
void Vector::print() const
{
	for (int i = 0; i < l; ++i) {
		cout << theVector[i] << " ";
	}
}
Vector Vector::read(ifstream & fileStream)
{
	bool initialized;
	fileStream >> initialized;
	if (!initialized) {
		return Vector();
	}
	int l;
	fileStream >> l;
	Vector r = Vector(l);

	double v;
	for (int i = 0; i < r.l; ++i) {
		fileStream >> v;
		r.theVector[i] = v;
	}
	return r;
}
void Vector::write(ofstream & outputStream)
{
	outputStream << initialized << ' ';
	if (!initialized) {
		cout << "saving non init" << endl;
		return;
	}
	outputStream << l << ' ';
	for (int i = 0; i < l; ++i) {
		outputStream << theVector[i] << ' ';
	}
}
const double& Vector::get(int x) const
{
	chkBounds(x);
	return theVector[x];
}
inline void Vector::chkBounds(const Vector & v) const
{
	if (l != v.l) {
		cout << "length mismatch  this.l = " << l << " param& l = " << v.l << endl;
		throw out_of_range("error");
	}
}
inline void Vector::chkBounds(int x) const {
	if (x < 0 || x >= l) {
		cout << " out of bounds --  assert! x > 0 || x < length - 1 " << endl;
		throw out_of_range("error");
	}
}