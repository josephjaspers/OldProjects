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
#include "jRNN.h"
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
		for (double d : v) {
			cout << d << " ";
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
	jRNN testSave(vector<int> {5, 6, 7, 8});
	ofstream output("savefileTest");
	testSave.write(output);
	output.close();

	cout << " reading " << endl;
	ifstream input("savefileTest");
	jRNN readTest;
	readTest.read(input);
	input.close();
	*/

	jRNN rnn(vector<int>{5, 200, 10});
	//should randomize training data
	rnn.addTrainingData(getZero(), vector<double> {1, 0, 0, 0, 0, 0, 0, 0, 0, 0});
	rnn.addTrainingData(getOne(), vector<double> {0, 1, 0, 0, 0, 0, 0, 0, 0, 0});
	rnn.addTrainingData(getTwo(), vector<double>   {0, 0, 1, 0, 0, 0, 0, 0, 0, 0});
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
		cout << " train " << endl;
		cin >> train;
		rnn.train(train);

		cout << "predict 0 " << endl;
		print(rnn.predict(getZero()));
		printConf(rnn.predict(getZero()));

		cout << " predict 1 " << endl;
		print(rnn.predict(getOne()));
		printConf(rnn.predict(getOne()));

		cout << " predict 2 " << endl;
		print(rnn.predict(getTwo()));
		printConf(rnn.predict(getTwo()));

		cout << " predict 3 " << endl;
		print(rnn.predict(getThree()));
		printConf(rnn.predict(getThree()));

		cout << " predict 4 " << endl;
		print(rnn.predict(getFour()));
		printConf(rnn.predict(getFour()));

		cout << " predict 5 " << endl;
		print(rnn.predict(getFive()));
		printConf(rnn.predict(getFive()));

		cout << " predict 6 " << endl;
		print(rnn.predict(getSix()));
		printConf(rnn.predict(getSix()));

		cout << " predict 7 " << endl;
		print(rnn.predict(getSeven()));
		printConf(rnn.predict(getSeven()));

		cout << " predict 8 " << endl;
		print(rnn.predict(getEight()));
		printConf(rnn.predict(getEight()));

		cout << " predict 9 " << endl;
		print(rnn.predict(getNine()));
		printConf(rnn.predict(getNine()));

	}

	cout << " saving " << endl;
	ofstream os("TESTFILE");
	rnn.write(os);
	os.close();
}