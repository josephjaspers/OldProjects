// Matrices_Test.cpp : Defines the entry point for the console application.
#include "Matrix.h"
#include "Vector.h"

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
	alpha.transpose().print();

	Matrix alphaT = Matrix(2, 3);
	alphaT[0] = 1; alphaT[1] = 4;
	alphaT[2] = 2; alphaT[3] = 5;
	alphaT[4] = 3; alphaT[5] = 6;

	alphaT.print();

	(alpha * beta).print();
	(alphaT.transpose() * beta).print();


	int wait;
	std::cin >> wait;
}
int GeneralTests()
{
	Matrix alpha = Matrix(3, 3);
	Matrix beta = Matrix(3, 3);
	for (int i = 0; i < alpha.size(); ++i) {
		alpha[i] = i + 1;
		beta[i] = i + 7;
	}
	alpha.print();
	beta.print();



	
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
	
	return 0;
}
void othertest() {

	Matrix alpha = Matrix(3, 2);
	Matrix beta = Matrix(2, 3);
//	Vector c = Vector();
	for (int i = 0; i < alpha.size(); ++i) {
		alpha[i] = i + 1;
		beta[i] = i + 7;
		
///		c[i] = i;
	}
	alpha.print();
	beta.print();

	alpha * beta;
	
	std::cout << " transpose time " << std::endl;

	Matrix alphaT = Matrix(2, 3);

	alphaT[0] = 1; alphaT[1] = 4;
	alphaT[2] = 2; alphaT[3] = 5;
	alphaT[4] = 3; alphaT[5] = 6;


	(alphaT->*beta).print();

	std::cout << " error hereo " << std::endl;

	alphaT.print();
	alphaT.transpose().print();

	std::cout << " erro here o " << std::endl;

	//(alphaT.transpose() * beta).print();
		
	Matrix m = alphaT.T();
	//(m * beta).print();

	std::cout << " rpitn " << std::endl;
	(alphaT ->* beta).print(); //dot transpose beta


}
void ConvertTest() {
	Matrix alpha = Matrix(2, 3);
	Matrix beta = Matrix(3, 2);
	Vector charles = Vector(3);
	for (int i = 0; i < alpha.size(); ++i) {
		alpha[i] = i + 1;
		beta[i] = i + 7;
	}
	for (int i = 0; i < charles.size(); ++i) {
		charles[i] = i;
	}
	std::cout << "alpha " << std::endl;
	alpha.print();
	std::cout << std::endl << " beta " << std::endl;
	beta.print();
	std::cout << std::endl << " charles " << std::endl;
	charles.print();
	std::cout << std::endl<< " alpha * beta  " << std::endl;
	(alpha * beta).print();
	std::cout << std::endl << " alpha * charles " << std::endl;
	(alpha * charles).print();
	std::cout << std::endl << " alpha.T() " << std::endl;
	(alpha.T()).print();
	std::cout << std::endl << " alpha.T() + beta " << std::endl;
	(alpha.T() + beta).print();
	std::cout << std::endl << " alpha.T() fill (3) " << std::endl;
	(alpha.T().fill(3)).print();

	int wait;
	std::cin >> wait;
}
void main() {
	Matrix alpha = Matrix(3, 2);
	Matrix beta = Matrix(3, 2);
	for (int i = 0; i < alpha.size(); ++i) {
		alpha[i] = i + 1;
		beta[i] = i + 7;
	}
	Vector v(3);
	for (int i = 0; i < 3; ++i) {
		v[i] = i;
	}
	std::cout << " alpha" << std::endl;
	alpha.print();
	std::cout << " beta " << std::endl;
	beta.print();
	std::cout << " alpha trans " << std::endl;
	alpha.transpose().print();

	Matrix alphaT = Matrix(3,2);
	alphaT[0] = 1; alphaT[1] = 4;
	alphaT[2] = 2; alphaT[3] = 5;
	alphaT[4] = 3; alphaT[5] = 6;

	alphaT.print();
//	beta.print();
//	(alpha * beta).print();
//	(alphaT ->* beta).print();
	v.print();

	(alphaT->*v).print();


	Vector v3 = Vector(100);
	for (int i = 0; i < v3.size(); ++i) {
		v3[i] = i;
	}

	std::cout << std::endl;
	Vector vcpy = v3;
	std::cout << " printing v " << std::endl;
	v3.print();
	std::cout << " rptining cpy " << std::endl;
	vcpy.print();

	int wait;
	std::cin >> wait;
}