	// Matrices_Test.cpp : Defines the entry point for the console application.
	#include "Matrix.h"

	//matrix by matrix tests

	//dot product
	void p(Matrix& a, Matrix& b) {
		(a * b).print();
	}
	void e(Matrix& a, Matrix& b) {
		(a ^ b).print();
	}void m(Matrix& a, Matrix& b) {
		(a & b).print();
	}void d(Matrix& a, Matrix& b) {
		(a / b).print();
	}void a(Matrix& a, Matrix& b) {
		(a + b).print();
	}void s(Matrix& a, Matrix& b) {
		(a - b).print();
	}

	//matrix by scalar tests

	void e(Matrix& a, double& d) {
		(a ^ d).print();
	}void m(Matrix& a, double& d) {
		(a & d).print();
	}void d(Matrix& a, double& d) {
		(a / d).print();
	}void a(Matrix& a, double& d) {
		(a + d).print();
	}void s(Matrix& a, double& d) {
		(a - d).print();
	}
	void transposeTest() {
		//123
		//456
		///
		//14
		//25
		//36

		Matrix alpha = Matrix(3, 2);
		Matrix beta = Matrix(2, 3);
		for (int i = 0; i < alpha.size(); ++i) {
			alpha[i] = i + 1;
			beta[i] = i + 7;
		}
		std::cout << " alpha" << std::endl;
		alpha.print();
		std::cout << " beta " << std::endl;
		beta.print();
		std::cout << " alpha trans " << std::endl;
	 Matrix& m  = alpha.transpose();

		Matrix alphaT = Matrix(2, 3);
		alphaT[0] = 1; alphaT[1] = 4;
		alphaT[2] = 2; alphaT[3] = 5;
		alphaT[4] = 3; alphaT[5] = 6;

		alphaT.print();

		(alpha * beta).print();


		int wait;
		std::cin >> wait;
	}
	int GeneralTests()
	{
		transposeTest();
	

		Matrix alpha = Matrix(3, 2);
		Matrix beta = Matrix(2, 3);
		for (int i = 0; i < alpha.size(); ++i) {
			alpha[i] = i + 1;
			beta[i] = i + 7;
		}
		alpha.print();
		beta.print();


		(alpha * beta).print();


		alpha.T().print();
		/*
		p(alpha, beta);
		e(alpha, beta);
		m(alpha, beta);
		d(alpha, beta);
		a(alpha, beta);
		s(alpha, beta);


		double vbeta = 2;

		e(alpha, vbeta);
		m(alpha, vbeta);
		d(alpha, vbeta);
		a(alpha, vbeta);
		s(alpha, vbeta);
		*/
	}
	int main() {
		transposeTest();
	}

