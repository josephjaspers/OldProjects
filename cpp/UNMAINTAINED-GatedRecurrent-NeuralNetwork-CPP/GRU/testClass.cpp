/*
* To change this license header, choose License Headers in Project Properties.
* To change this template file, choose Tools | Templates
* and open the template in the editor.
*/

/*
* File:   main.cpp
* Author: joeyj
*
* Created on December 26, 2016, 2:22 PM
*/
#include "stdafx.h"
#include <cstdlib>
#include "GRU.h"
#include "Matrix.h"
#include <fstream>
#include <ostream>
#include <iostream>
#include <cstdlib>
#include <string>
#include <list>
#include <string>
#include <sstream>

using namespace std;

namespace testClass {
	void print(vector<double> v) {
		cout.precision(1);
		for (double dz : v) {
			cout << dz << " ";
		}
		cout << endl;

	}
	void printConf(vector<double> v) {
		cout.precision(2);
		int index = -1;
		double best = 0;
		for (int i = 0; i < v.size(); ++i) {
			if (v[i] > best) {
				best = v[i];
				index = i;
			}
		}
		cout << "(" << index << ")" << " conf (" << best << ")" << endl << endl;
	}

	vector<vector<double>> getZero() {
		vector<double> r1 = { 0,0,1,0,0 };
		vector<double> r2 = { 0,1,0,1,0 };
		vector<double> r3 = { 0,1,0,1,0 };
		vector<double> r4 = { 0,1,0,1,0 };
		vector<double> r5 = { 0,0,1,0,0 };

		vector<vector<double>> n = { r1,r2,r3,r4,r5 };
		return n;
	}
	vector<vector<double>> getOne() {
		vector<double> r1 = { 0,1,1,0,0 };
		vector<double> r2 = { 0,0,1,0,0 };
		vector<double> r3 = { 0,0,1,0,0 };
		vector<double> r4 = { 0,0,1,0,0 };
		vector<double> r5 = { 0,1,1,1,0 };

		vector<vector<double>> n = { r1,r2,r3,r4,r5 };
		return n;
	}
	vector<vector<double>> getTwo() {
		vector<double> r1 = { 0,1,1,1,0 };
		vector<double> r2 = { 0,0,0,1,0 };
		vector<double> r3 = { 0,0,1,0,0 };
		vector<double> r4 = { 0,1,0,0,0 };
		vector<double> r5 = { 0,1,1,1,0 };

		vector<vector<double>> n = { r1,r2,r3,r4,r5 };
		return n;
	}
	vector<vector<double>> getThree() {
		vector<double> r1 = { 0,1,1,1,0 };
		vector<double> r2 = { 0,0,0,1,0 };
		vector<double> r3 = { 0,1,1,1,0 };
		vector<double> r4 = { 0,0,0,1,0 };
		vector<double> r5 = { 0,1,1,1,0 };

		vector<vector<double>> n = { r1,r2,r3,r4,r5 };
		return n;
	}
	vector<vector<double>> getFour() {
		vector<double> r1 = { 0,1,0,1,0 };
		vector<double> r2 = { 0,1,0,1,0 };
		vector<double> r3 = { 0,1,1,1,1 };
		vector<double> r4 = { 0,0,0,1,0 };
		vector<double> r5 = { 0,0,0,1,0 };

		vector<vector<double>> n = { r1,r2,r3,r4,r5 };
		return n;
	}
	vector<vector<double>> getFive() {
		vector<double> r1 = { 0,1,1,1,0 };
		vector<double> r2 = { 0,1,0,0,0 };
		vector<double> r3 = { 0,1,1,1,0 };
		vector<double> r4 = { 0,0,0,1,0 };
		vector<double> r5 = { 0,1,1,1,0 };

		vector<vector<double>> n = { r1,r2,r3,r4,r5 };
		return n;
	}
	vector<vector<double>> getSix() {
		vector<double> r1 = { 0,1,0,0,0 };
		vector<double> r2 = { 0,1,0,0,0 };
		vector<double> r3 = { 0,1,1,1,0 };
		vector<double> r4 = { 0,1,0,1,0 };
		vector<double> r5 = { 0,1,1,1,0 };

		vector<vector<double>> n = { r1,r2,r3,r4,r5 };
		return n;
	}
	vector<vector<double>> getSeven() {
		vector<double> r1 = { 0,1,1,0,0 };
		vector<double> r2 = { 0,0,0,1,0 };
		vector<double> r3 = { 0,0,1,1,0 };
		vector<double> r4 = { 0,1,0,0,0 };
		vector<double> r5 = { 0,1,0,0,0 };

		vector<vector<double>> n = { r1,r2,r3,r4,r5 };
		return n;
	}
	vector<vector<double>> getEight() {
		vector<double> r1 = { 0,1,1,1,0 };
		vector<double> r2 = { 0,1,0,1,0 };
		vector<double> r3 = { 0,1,1,1,0 };
		vector<double> r4 = { 0,1,0,1,0 };
		vector<double> r5 = { 0,1,1,1,0 };

		vector<vector<double>> n = { r1,r2,r3,r4,r5 };
		return n;
	}
	vector<vector<double>> getNine() {
		vector<double> r1 = { 0,1,1,1,0 };
		vector<double> r2 = { 0,1,0,1,0 };
		vector<double> r3 = { 0,1,1,1,0 };
		vector<double> r4 = { 0,0,0,1,0 };
		vector<double> r5 = { 0,0,0,1,0 };

		vector<vector<double>> n = { r1,r2,r3,r4,r5 };
		return n;
	}
}

using namespace testClass;
int main() {

	/*
	cout << "saving " << endl;
	GRU testSave(vector<int> {5, 6, 7, 8});
	ofstream output("savefileTest");
	testSave.write(output);
	x
	cout << " reading " << endl;
	ifstream input("savefileTest");
	GRU readTest;
	readTest.read(input);
	input.close();
	*/

	GRU rnn(vector<int>{5, 25, 10});
	//should randomize training data
	rnn.addTrainingData(getZero(), vector<double> {1, 0, 0, 0, 0, 0, 0, 0, 0, 0});
	rnn.addTrainingData(getOne(), vector<double>  {0, 1, 0, 0, 0, 0, 0, 0, 0, 0});
	rnn.addTrainingData(getTwo(), vector<double>  {0, 0, 1, 0, 0, 0, 0, 0, 0, 0});
	rnn.addTrainingData(getThree(), vector<double>{0, 0, 0, 1, 0, 0, 0, 0, 0, 0});
	rnn.addTrainingData(getFour(), vector<double> {0, 0, 0, 0, 1, 0, 0, 0, 0, 0});
	rnn.addTrainingData(getFive(), vector<double> {0, 0, 0, 0, 0, 1, 0, 0, 0, 0});
	rnn.addTrainingData(getSix(), vector<double>  {0, 0, 0, 0, 0, 0, 1, 0, 0, 0});
	rnn.addTrainingData(getSeven(), vector<double>{0, 0, 0, 0, 0, 0, 0, 1, 0, 0});
	rnn.addTrainingData(getEight(), vector<double>{0, 0, 0, 0, 0, 0, 0, 0, 1, 0});
	rnn.addTrainingData(getNine(), vector<double> {0, 0, 0, 0, 0, 0, 0, 0, 0, 1});


	//	ifstream is("TESTFILE");
	//	rnn.read(is);
	//	is.close();

	int train = 1;
	while (train > 0) {
		cout << " learning rate is " << rnn.getLearningRate() << endl;
		cout << " train " << endl;
		cin >> train;

		if (train == -1) {
			cout << " adj learing rate ? " << endl;
			train = 1;

			double lr;
			cin >> lr;
			rnn.setLearningRate(lr);
		}

		rnn.train(train);

		cout << "predict 0 " << endl;
		vector<double>& t0 = rnn.predict(getZero());
		print(t0);
		printConf(t0);

		cout << " predict 1 " << endl;
		vector<double>& t1 = rnn.predict(getOne());
		print(t1);
		printConf(t1);

		cout << " predict 2 " << endl;
		vector<double>& t2 = rnn.predict(getTwo());
		print(t2);
		printConf(t2);

		cout << " predict 3 " << endl;
		vector<double>& t3 = rnn.predict(getThree());
		print(t3);
		printConf(t3);

		cout << " predict 4 " << endl;
		vector<double>& t4 = rnn.predict(getFour());
		print(t4);
		printConf(t4);

		cout << " predict 5 " << endl;
		vector<double>& t5 = rnn.predict(getFive());
		print(t5);
		printConf(t5);

		cout << " predict 6 " << endl;
		vector<double>& t6 = rnn.predict(getSix());
		print(t6);
		printConf(t6);

		cout << " predict 7 " << endl;
		vector<double>& t7 = rnn.predict(getSeven());
		print(t7);
		printConf(t7);


		cout << " predict 8 " << endl;
		vector<double>& t8 = rnn.predict(getEight());
		print(t8);
		printConf(t8);

		cout << " predict 9 " << endl;
		vector<double>& t9 = rnn.predict(getNine());
		print(t9);
		printConf(t9);

	}
}