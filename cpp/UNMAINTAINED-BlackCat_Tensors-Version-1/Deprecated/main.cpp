//#include "Vector.h"
//#include "Matrix.h"
//
//
//template<typename T>
//void passTo(T value) {
//	std::cout <<" passed " << std::endl;
//
//	value = value + value;
//	value.print();
//}
//
//int randomTests() {
//
//	std::cout << " Creating " << std::endl;
//
//	Vector<float> a(5);
//	Vector<double> b(5);
//	Vector<float> c(5);
//	Vector<float> d(5);
//
////
//	Matrix<float> m(5, 5);
//
//	m[0] = Scalar<float>(4);
//
//	m.print();
//	std::cout << std::endl;
//
//	std::cout << "printing A" << std::endl;
//	a.randomize(-3, 3);
//
//	a.print();
//	m[1] = m[1] + a;
//	m[2] = m[1] % m[2];
//
//	m.print();
//
//	a = Scalar<float>(4);
//	a.print(7);
//	std::cout << std::endl;
//
//	std::cout << "printing B" << std::endl;
//	b.randomize(-3, 3);
//	b.print();
//	std::cout << std::endl;
//
//	std::cout << "printing A+B" << std::endl;
//	c = a + b;
//	c.print();
//	std::cout << std::endl;
//
//	std::cout << "printing A=b" << std::endl;
//	a = b;
//	a.print();
//	std::cout << std::endl;
//
//	std::cout << "printing sub vector at index [1] size 3" << std::endl;
//	a(1, 3).print();
//	std::cout << std::endl;
//
//	std::cout << "printing a(1,5) = a(1,5) % b[2] --- % is the pointwise multiply operand " << std::endl;
//	std::cout << " b[2] = ";
//	b[2].print();
//	std::cout << std::endl;
//
//	a(1, 3) = a(1, 3) % b[2];
//	a(1, 3).print();
//	std::cout << std::endl;
//
//	std::cout << " reprinting a (full size) " << std::endl;
//	a.print();
//	std::cout << std::endl;
//
//	//std::cout << " success " << std::endl;
//
//	passTo(a);
//	passTo(b);
//
//
//	a = a + b;
//
//	std::cout << std::endl;
//	std::cout << " success " << std::endl;
//	return 0;
//}
//
//int main() {
//
//	Matrix<float> a(2,3);
//	Matrix<float> b(3,2);
//
//
//	for (int i = 0; i < a.size(); ++i) {
//		a.accessor()[i] = i + 1;
//		b.accessor()[i] = i + 7;
//	}
//
//	a.print();
//	std::cout << std::endl << std::endl;
//
//	b.print();
//
//	std::cout << std::endl << std::endl;
//
//	(a * b).print();
//
//}
