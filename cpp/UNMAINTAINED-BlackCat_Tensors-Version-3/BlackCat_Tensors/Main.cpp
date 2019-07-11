/*
 * Main.cpp
 *
 *  Created on: Dec 6, 2017
 *      Author: joseph
 */

#include "BC_Internals/BlackCat_Internal_GlobalUnifier.h"
using namespace BC;

int VectorTests() {

	Tensor_Shape<Inner_Shape<2, 3, 4>> sh;

	sh.printDimensions();
	sh.printLeadingDimensions();

	Vector<double, 10> vec;
	Vector<double, 10> vec1;

	Vector<double, 10> vec2;

	vec1.randomize(10, 20);
	vec1.print();
	vec2.randomize(1, 10);
	vec2.print();

	vec = vec1 + vec2 + vec1;
	std::cout << " adding vec1 + vec2 and eval " << std::endl;
	(vec1 + vec2).eval();

	//(vec1 + vec2) = vec1;

	vec.print();
	vec[2].print();

	vec = vec2;
	vec = vec + vec;
	vec.print();

//	vec * vec2.t();

//	vec * vec2.t();

	Matrix<double, 10, 10> mat;

	std::cout << "vec trans = " << std::endl;

	Matrix<double, 10, 2> mat3;
	Matrix<double, 2, 10> mat4 = mat3.t();
	//vec.t();
	//vec.t();//.t();

//	mat3.t();

	RowVector<double, 10> m = vec.t();
	m.print();

	std::cout << "success " << std::endl;

	return 0;
}

int main() {
	VectorTests();

	Cube<double, 3, 4, 2> cub;
	cub.randomize(0, 400);
	cub.print();

	Matrix<double, 3, 4> mat;
	Matrix<double, 3, 4> mat1;
	Matrix<double, 3, 4> mat2;

	mat1.randomize(0, 100);
	mat2.randomize(0, 100);

	mat1.print();
	mat2.print();

	std::cout << "expression " << std::endl;
	mat = mat1 / mat2 + mat1 % mat2;
	mat.print();

	std::cout << " standard const Matrix<params>& constructor" << std::endl;
	Matrix<double, 3, 4> con = mat;

	std::cout << " copy assignment" << std::endl;
	con = mat;

	std::cout << " mat " << std::endl;
	mat.print();

	std::cout << " transpose mat " << std::endl;

	Matrix<double, 4, 3> matT;

	matT = mat.t();
	matT.print();

	std::cout << "success " << std::endl;



	Vector<double> dub = {10};
	Matrix<double> dub2 = {10, 12};

		dub2.print();

	dub.printDimensions();
	dub.printLeadingDimensions();

	dub2.printDimensions();
	dub2.printLeadingDimensions();

	std::cout << "success 2" << std::endl;
	std::cout << "eval " << std::endl;

	Vector<double, 8> vec1;
	RowVector<double, 6> vec2;

	Matrix<double, 8, 6> mat3;

	vec1.randomize(0, 5);
	vec2.randomize(0, 5);

	vec1.print();
	vec2.print();

	std::cout << " utiltiy creation: " << std::endl;

	std::cout << " asdf " << std::endl;

	mat3.print();


	std::cout << "finising " << std::endl;
	return 0;


}
