#include "stdafx.h"
#include "Matrices.h"

#include <vector>
int main() {
	//_CrtSetDbgFlag(_CRTDBG_CHECK_ALWAYS_DF);
	vector<Matrix> matrixNet = vector<Matrix>(5);
		matrixNet.push_back(Matrix(2,4));
		matrixNet[0] = Matrix(3, 4);
		cout << " done main " << endl;

		Matrix m = Matrix(matrixNet[0]);

		int wait;
		cin >> wait;
		/*
		matrixNet.push_back(Matrix(5, 6));
		cout << "exceed" << endl;
		matrixNet.push_back(Matrix(6, 7));


		vector<Vector> net = vector<Vector>(3);
		cout << " main " << endl;
		net.push_back(Vector(3));
		net.push_back(Vector(4));


		auto net2 = net;
		return 0;
		*/

}