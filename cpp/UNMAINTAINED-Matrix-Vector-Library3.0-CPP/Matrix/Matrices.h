#include <vector>
#include <cstdlib>
#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <ostream>
#include "Matrix.h"
#include "Vector.h"
#include <iostream>

namespace Matrices {
	static Vector & exp(Vector & s, Vector & m1, Vector & m2)
	{
		for (int i = 0; i < s.length(); ++i) {
			s[i] = pow(m1[i], m2[i]);
		}
		return s;
	}
	static Vector & mult(Vector & s, Vector & m1, Vector & m2)
	{
		for (int i = 0; i < s.length(); ++i) {
			s[i] = m1[i] * m2[i];
		}
		return s;
	}
	static Vector & multSum(Vector & s, Vector & m1, Vector & m2)
	{
		for (int i = 0; i < s.length(); ++i) {
			s[i] += m1[i] * m2[i];
		}
		return s;
	}
	static Vector & div(Vector & s, Vector & m1, Vector & m2)
	{
		for (int i = 0; i < s.length(); ++i) {
			s[i] = m1[i] / m2[i];
		}
		return s;
	}
	static Vector & add(Vector & s, Vector & m1, Vector & m2)
	{
		for (int i = 0; i < s.length(); ++i) {
			//cout << m2[i] << endl;
			s[i] = m1[i] + m2[i];
		}
		return s;
	}
	static Vector & sub(Vector & s, Vector & m1, Vector & m2)
	{
		for (int i = 0; i < s.length(); ++i) {
			s[i] = m1[i] - m2[i];
		}
		return s;
	}
	static Vector& dot(Vector & s, Vector & m, Vector & v)
	{
		double tmp;
		for (int l = 0; l < m.length(); ++l) {
			tmp = 0;
			for (int l2 = 0; l2 < v.length(); ++l2) {
				tmp += m(l) * v(l2);
			}
			s(l) = tmp;
		}
		return s;
	}
	static Vector exp(Vector & m1, Vector & m2)
	{
		Vector v = Vector(m1.size());
		for (int i = 0; i < v.size(); ++i) {
			v[i] = pow(m1[i], m2[i]);
		}
		return v;
	}
	static Vector mult(Vector & m1, Vector & m2)
	{
		Vector v(m1.size());
		for (int i = 0; i < v.size(); ++i) {
			v[i] = m1[i] * m2[i];
		}
		return v;
	}
	static Vector div(Vector & m1, Vector & m2)
	{
		Vector v(m1.size());
		for (int i = 0; i < v.size(); ++i) {
			v[i] = m1[i] / m2[i];
		}
		return v;
	}
	static Vector add(Vector & m1, Vector & m2)
	{
		Vector v(m1.size());
		for (int i = 0; i < v.size(); ++i) {
			v[i] = m1[i] + m2[i];
		}
		return v;
	}
	static Vector sub(Vector & m1, Vector & m2)
	{
		Vector v(m1.size());
		for (int i = 0; i < v.size(); ++i) {
			v[i] = m1[i] - m2[i];
		}
		return v;
	}
	static Matrix dot(Vector & v1, Vector & v2)
	{
		Matrix m(v1.length(), v2.length());
		for (int l1 = 0; l1 < v1.length(); ++l1) {
			for (int l2 = 0; l2 < v2.length(); ++l2) {
				m(l1, l2) = v1[l1] * v2[l2];
			}
		}
		return m;
	}
	static Vector & dot(Vector & s, Matrix & m, Vector & v)
	{
		if (m.width() != v.length()) {
			cout << " param m.width = " << m.width() << " v length = " << v.length() << endl;
			throw range_error("Dot Product length/width mismatch");
		}
		//Matrix mat(length(), m.width());
		for (int l = 0; l < m.length(); ++l) {
			double tmp = 0;
			for (int l2 = 0; l2 < v.length(); ++l2) {
				tmp += m(l, l2) * v(l2);
			}
			s(l) = tmp;
		}
		return s;
	}
	static Vector dot(Matrix & m, Vector & v)
	{
		if (m.width() != v.length()) {
			cout << " param m.width = " << m.width() << " v length = " << v.length() << endl;
			throw range_error("Dot Product length/width mismatch");
		}
		Vector s = Vector(m.length());

		for (int l = 0; l < m.length(); ++l) {
			double tmp = 0;
			for (int l2 = 0; l2 < v.length(); ++l2) {
				tmp += m(l, l2) * v(l2);
			}
			s(l) = tmp;
		}
		return s;
	}
	static Vector & dotSum(Vector & s, Matrix & m, Vector & v)
	{
		if (m.width() != v.length()) {
			cout << " param m.width = " << m.width() << " v length = " << v.length() << endl;
			throw range_error("Dot Product length/width mismatch");
		}
		//Matrix mat(length(), m.width());
		for (int l = 0; l < m.length(); ++l) {
			double tmp = 0;
			for (int l2 = 0; l2 < v.length(); ++l2) {
				tmp += m(l, l2) * v(l2);
			}
			s(l) += tmp;
		}
		return s;
	}
	static Vector & dotSub(Vector & s, Matrix & m, Vector & v)
	{
		if (m.width() != v.length()) {
			cout << " param m.width = " << m.width() << " v length = " << v.length() << endl;
			throw range_error("Dot Product length/width mismatch");
		}
		//Matrix mat(length(), m.width());
		for (int l = 0; l < m.length(); ++l) {
			double tmp = 0;
			for (int l2 = 0; l2 < v.length(); ++l2) {
				tmp += m(l, l2) * v(l2);
			}
			s(l) -= tmp;
		}
		return s;
	}
	static Vector& dotTranspose(Vector& s, Matrix& m, Vector& v) {
		//matrix width = length

		if (m.length() != v.length()) {
			throw range_error("Dot Product length/width mismatch");
		}
		//Matrix mat(length(), m.width());
		for (int l = 0; l < m.width(); ++l) {
			double tmp = 0;
			for (int l2 = 0; l2 < v.length(); ++l2) {
				tmp += m(l2, l) * v(l2);
			}
			s(l) = tmp;
		}
		return s;
	}
	static Vector dotTranspose(Matrix& m, Vector& v) {
		//matrix width = length

		if (m.length() != v.length()) {
			throw range_error("Dot Product length/width mismatch");
		}
		Vector s = Vector(m.width());
		//Matrix mat(length(), m.width());
		for (int l = 0; l < m.width(); ++l) {
			double tmp = 0;
			for (int l2 = 0; l2 < v.length(); ++l2) {
				tmp += m(l2, l) * v(l2);
			}
			s(l) = tmp;
		}
		return s;
	}
	//Static Matrix Methods --optimized version
	static Matrix & exp(Matrix & s, Matrix & m1, Matrix & m2)
	{
		for (int l = 0; l < s.length(); ++l) {
			for (int w = 0; w < s.width(); ++w) {
				s(l, w) = pow(m1(l, w), m2(l, w));
			}
		}
		return s;
	}
	static Matrix & mult(Matrix & s, Matrix & m1, Matrix & m2)
	{
		for (int l = 0; l < s.length(); ++l) {
			for (int w = 0; w < s.width(); ++w) {
				s(l, w) = m1(l, w) * m2(l, w);
			}
		}
		return s;
	}
	static Matrix & div(Matrix & s, Matrix & m1, Matrix & m2)
	{
		for (int l = 0; l < s.length(); ++l) {
			for (int w = 0; w < s.width(); ++w) {
				s(l, w) = m1(l, w) / m2(l, w);
			}
		}
		return s;
	}
	static Matrix & add(Matrix & s, Matrix & m1, Matrix & m2)
	{
		for (int l = 0; l < s.length(); ++l) {
			for (int w = 0; w < s.width(); ++w) {
				s(l, w) = m1(l, w) + m2(l, w);
			}
		}
		return s;
	}
	static Matrix & sub(Matrix & s, Matrix & m1, Matrix & m2)
	{
		for (int l = 0; l < s.length(); ++l) {
			for (int w = 0; w < s.width(); ++w) {
				s(l, w) = m1(l, w) - m2(l, w);
			}
		}
		return s;
	}
	static Matrix & dot(Matrix & s, Matrix & m1, Matrix & m2)
	{
		if (m1.width() != m2.length()) {
			throw range_error("Dot Product length/width mismatch");
		}
		//Matrix mat(length(), m.width());
		double tmp;
		for (int l = 0; l < m1.length(); ++l) {
			for (int w = 0; w < m2.width(); ++w) {
				tmp = 0;
				for (int l2 = 0; l2 < m2.length(); ++l2) {
					tmp += m1(l, l2) * m2(l2, w);
				}
				s(l, w) = tmp;
			}
		}
		return s;
	}
	static Matrix exp(Matrix & m1, Matrix & m2)
	{
		Matrix r = Matrix(m1.length(), m1.width());
		for (int l = 0; l < r.length(); ++l) {
			for (int w = 0; w < r.width(); ++w) {
				r(l, w) = pow(m1(l, w), m2(l, w));
			}
		}
		return r;
	}
	static Matrix mult(Matrix & m1, Matrix & m2) {
		Matrix r = Matrix(m1.length(), m1.width());
		for (int l = 0; l < r.length(); ++l) {
			for (int w = 0; w < r.width(); ++w) {
				r(l, w) = m1(l, w) * m2(l, w);
			}
		}
		return r;
	}
	static Matrix div(Matrix & m1, Matrix & m2)
	{
		Matrix r = Matrix(m1.length(), m1.width());
		for (int l = 0; l < r.length(); ++l) {
			for (int w = 0; w < r.width(); ++w) {
				r(l, w) = m1(l, w) / m2(l, w);
			}
		}
		return r;
	}
	static Matrix add(Matrix & m1, Matrix & m2)
	{
		Matrix r = Matrix(m1.length(), m1.width());
		for (int l = 0; l < r.length(); ++l) {
			for (int w = 0; w < r.width(); ++w) {
				r(l, w) = m1(l, w) + m2(l, w);
			}
		}
		return r;
	}
	static Matrix sub(Matrix & m1, Matrix & m2)
	{
		Matrix r = Matrix(m1.length(), m1.width());
		for (int l = 0; l < r.length(); ++l) {
			for (int w = 0; w < r.width(); ++w) {
				r(l, w) = m1(l, w) - m2(l, w);
			}
		}
		return r;
	}
	//static Vector - stdVector<double>
	static Vector & sub(Vector& s, Vector& v, vector<double> v2) {
		for (int i = 0; i < s.size(); ++i) {
			s[i] = v[i] - v2[i];
		}
		return s;
	}
	static Vector & dot(Vector & s, Matrix & m, vector<double> & v)
	{
		if (m.width() != v.size()) {
			throw range_error("Dot Product length/width mismatch");
		}
		//Matrix mat(length(), m.width());
		for (int l = 0; l < m.length(); ++l) {
			double tmp = 0;
			for (int l2 = 0; l2 < v.size(); ++l2) {
				tmp += m(l, l2) * v[l2];
			}
			s(l) = tmp;
		}
		return s;
	}
	//randomize in range
	static Vector& randomize(Vector& v, int min, int max) {
		for (int i = 0; i < v.length(); ++i) {
			v[i] = (rand() & max) + min;
		}
		return v;
	}
	static Matrix& randomize(Matrix& m, int min, int max) {
		for (int x = 0; x < m.length(); ++x) {
			for (int y = 0; y < m.width(); ++y) {
				m(x, y) = (rand() & max) + min;
			}
		}
		return m;
	}


	static Matrix operator*(const Vector& v1, const Vector& v2) {
		Matrix m(v1.length(), v2.length());
		for (int l1 = 0; l1 < v1.length(); ++l1) {
			for (int l2 = 0; l2 < v2.length(); ++l2) {
				m(l1, l2) = v1.get(l1) * v2.get(l2);
			}
		}
		return m;
	}//outer product
	static Vector operator*(const Matrix& m, const Vector& v) {
		if (m.width() != v.length()) {
			cout << " param m.width = " << m.width() << " v length = " << v.length() << endl;
			throw range_error("Dot Product length/width mismatch");
		}
		Vector s = Vector(m.length());
		//Matrix mat(length(), m.width());
		for (int l = 0; l < m.length(); ++l) {
			double tmp = 0;
			for (int l2 = 0; l2 < v.length(); ++l2) {
				tmp += m.get(l, l2) * v.get(l2);
			}
			s(l) = tmp;
		}
		return s;
	}
};