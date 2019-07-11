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
#include "jANN.h"

using namespace std;
namespace testclass {

void print(vector<double> v) {
	cout.precision(1);
	for (double d : v) {
		cout << d << " ";
	}
	cout << endl;

}
void printConf(vector<double> v) {
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
vector<double> getZero() {
	vector<double> n = 
	  { 0,0,1,0,0,
		0,1,0,1,0,
		0,1,0,1,0,
		0,1,0,1,0,
		0,0,1,0,0, };
	return n;
}
vector<double> getOne() {
	vector<double> n =
	  { 0,1,1,0,0,
		0,0,1,0,0,
		0,0,1,0,0,
		0,0,1,0,0,
		0,1,1,1,0, };
	return n;
}
vector<double> getTwo() {
	vector<double> n =
	  { 0,1,1,1,0,
		0,0,0,1,0,
		0,0,1,0,0,
		0,1,0,0,0,
		0,1,1,1,0, };
	return n;
}
vector<double> getThree() {
	vector<double> n =
	  { 0,1,1,1,0,
		0,0,0,1,0,
		0,1,1,1,0,
		0,0,0,1,0,
		0,1,1,1,0, };
	return n;
}
vector<double> getFour() {
	vector<double> n =
	{ 0,1,0,1,0,
		0,1,0,1,0,
		0,1,1,1,1,
		0,0,0,1,0,
		0,0,0,1,0, };
	return n;
}
vector<double> getFive() {
	vector<double> n =
	{ 0,1,1,1,0,
		0,1,0,0,0,
		0,1,1,1,0,
		0,0,0,1,0,
		0,1,1,1,0, };
	return n;
}
vector<double> getSix() {
	vector<double> n =
	{ 0,1,1,1,0,
		0,1,0,0,0,
		0,1,1,1,0,
		0,1,0,1,0,
		0,1,1,1,0, };
	return n;
}
vector<double> getSeven() {
	vector<double> n =
	{ 0,1,1,1,0,
		0,0,0,1,0,
		0,0,1,0,0,
		0,1,0,0,0,
		0,1,0,0,0, };
	return n;
}
vector<double> getEight() {
	vector<double> n =
	{ 0,1,1,1,0,
		0,1,0,1,0,
		0,1,1,1,0,
		0,1,0,1,0,
		0,1,1,1,0, };
	return n;
}
vector<double> getNine() {
	vector<double> n =
	{ 0,1,1,1,0,
		0,1,0,1,0,
		0,1,1,1,0,
		0,0,0,1,0,
		0,0,0,1,0, };
	return n;
}

int DRTest() {
	jANN rnn(vector<int> { 25, 435, 10});

	ifstream is("testfile");
	rnn.read(is);
	is.close();

	rnn.addTrainingData(getZero(), vector<double>  {1, 0, 0, 0, 0, 0, 0, 0, 0, 0});
	rnn.addTrainingData(getOne(), vector<double>   {0, 1, 0, 0, 0, 0, 0, 0, 0, 0});
	rnn.addTrainingData(getTwo(), vector<double>   {0, 0, 1, 0, 0, 0, 0, 0, 0, 0});
	rnn.addTrainingData(getThree(), vector<double> {0, 0, 0, 1, 0, 0, 0, 0, 0, 0});
	rnn.addTrainingData(getFour(), vector<double>  {0, 0, 0, 0, 1, 0, 0, 0, 0, 0});
	rnn.addTrainingData(getFive(), vector<double>  {0, 0, 0, 0, 0, 1, 0, 0, 0, 0});
	rnn.addTrainingData(getSix(), vector<double>   {0, 0, 0, 0, 0, 0, 1, 0, 0, 0});
	rnn.addTrainingData(getSeven(), vector<double> {0, 0, 0, 0, 0, 0, 0, 1, 0, 0});
	rnn.addTrainingData(getEight(), vector<double> {0, 0, 0, 0, 0, 0, 0, 0, 1, 0});
	rnn.addTrainingData(getNine(), vector<double>  {0, 0, 0, 0, 0, 0, 0, 0, 0, 1});



	int train = 1;
	while (train > 0) {
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

		cout << " train " << endl;
		cin >> train;
		rnn.train(train);
	}
	cout << " saving endl " << endl;
	ofstream os("testfile");
	rnn.write(os);
	os.close();

	int wait;
	cin >> wait;
	return 0;
}
void DRTestLarge() {
	jANN net = jANN(vector<int> { 784, 250, 10});

	//0
	net.addTrainingData(vector<double> {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 18, 30, 137, 137, 192, 86, 72, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 13, 86, 250, 254, 254, 254, 254, 217, 246, 151, 32, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 16, 179, 254, 254, 254, 254, 254, 254, 254, 254, 254, 231, 54, 15, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 72, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 104, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 61, 191, 254, 254, 254, 254, 254, 109, 83, 199, 254, 254, 254, 254, 243, 85, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 172, 254, 254, 254, 202, 147, 147, 45, 0, 11, 29, 200, 254, 254, 254, 171, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 174, 254, 254, 89, 67, 0, 0, 0, 0, 0, 0, 128, 252, 254, 254, 212, 76, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 47, 254, 254, 254, 29, 0, 0, 0, 0, 0, 0, 0, 0, 83, 254, 254, 254, 153, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 80, 254, 254, 240, 24, 0, 0, 0, 0, 0, 0, 0, 0, 25, 240, 254, 254, 153, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 64, 254, 254, 186, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 166, 254, 254, 224, 12, 0, 0, 0, 0, 0, 0, 0, 0, 14, 232, 254, 254, 254, 29, 0, 0, 0, 0, 0, 0, 0, 0, 0, 75, 254, 254, 254, 17, 0, 0, 0, 0, 0, 0, 0, 0, 18, 254, 254, 254, 254, 29, 0, 0, 0, 0, 0, 0, 0, 0, 0, 48, 254, 254, 254, 17, 0, 0, 0, 0, 0, 0, 0, 0, 2, 163, 254, 254, 254, 29, 0, 0, 0, 0, 0, 0, 0, 0, 0, 48, 254, 254, 254, 17, 0, 0, 0, 0, 0, 0, 0, 0, 0, 94, 254, 254, 254, 200, 12, 0, 0, 0, 0, 0, 0, 0, 16, 209, 254, 254, 150, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 15, 206, 254, 254, 254, 202, 66, 0, 0, 0, 0, 0, 21, 161, 254, 254, 245, 31, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 60, 212, 254, 254, 254, 194, 48, 48, 34, 41, 48, 209, 254, 254, 254, 171, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 86, 243, 254, 254, 254, 254, 254, 233, 243, 254, 254, 254, 254, 254, 86, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 114, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 239, 86, 11, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 13, 182, 254, 254, 254, 254, 254, 254, 254, 254, 243, 70, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8, 76, 146, 254, 255, 254, 255, 146, 19, 15, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
	}, vector<double>{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0});
	//1
	net.addTrainingData(vector<double> {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 188, 255, 94, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 191, 250, 253, 93, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 123, 248, 253, 167, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 80, 247, 253, 208, 13, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 29, 207, 253, 235, 77, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 54, 209, 253, 253, 88, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 93, 254, 253, 238, 170, 17, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 23, 210, 254, 253, 159, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 16, 209, 253, 254, 240, 81, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 27, 253, 253, 254, 13, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 20, 206, 254, 254, 198, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 168, 253, 253, 196, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 20, 203, 253, 248, 76, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 22, 188, 253, 245, 93, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 103, 253, 253, 191, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 89, 240, 253, 195, 25, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 15, 220, 253, 253, 80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 94, 253, 253, 253, 94, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 89, 251, 253, 250, 131, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 214, 218, 95, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
	}, vector<double> {0, 1, 0, 0, 0, 0, 0, 0, 0, 0});
	//2
	net.addTrainingData(vector<double>{
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 39, 91, 91, 91, 91, 91, 191, 255, 142, 91, 23, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 23, 211, 253, 253, 253, 253, 253, 253, 253, 253, 253, 181, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 180, 253, 253, 253, 253, 253, 253, 253, 253, 253, 253, 228, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 180, 253, 253, 253, 253, 253, 253, 253, 253, 253, 253, 228, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 101, 253, 253, 253, 253, 253, 253, 253, 253, 253, 253, 228, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 14, 224, 253, 253, 211, 114, 96, 253, 253, 253, 253, 228, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 48, 204, 114, 18, 0, 156, 253, 253, 253, 253, 228, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 15, 0, 0, 0, 230, 253, 253, 253, 253, 185, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 31, 156, 244, 253, 253, 253, 192, 25, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 209, 253, 253, 253, 253, 245, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5, 215, 253, 253, 253, 245, 130, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 124, 253, 253, 253, 253, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 41, 220, 253, 253, 253, 238, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 49, 222, 253, 253, 253, 253, 98, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 107, 253, 253, 253, 253, 210, 35, 0, 0, 0, 5, 42, 42, 42, 42, 18, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 107, 253, 253, 253, 253, 253, 178, 131, 131, 131, 143, 253, 253, 253, 253, 182, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 83, 240, 253, 253, 253, 253, 253, 253, 253, 253, 253, 253, 253, 253, 240, 195, 12, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 197, 253, 253, 253, 253, 253, 253, 253, 253, 253, 253, 229, 106, 82, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 33, 179, 241, 253, 253, 253, 253, 253, 253, 246, 179, 44, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 75, 89, 195, 89, 89, 89, 89, 81, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
	}, vector<double> {0, 0, 1, 0, 0, 0, 0, 0, 0, 0});
//3

	int train = 1;
	while (train > 0) {
		cout << "train " << endl;
		cin >> train;
		net.train(train);
		cout << " 0 " << endl;
		printConf(net.predict(vector<double> {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 18, 30, 137, 137, 192, 86, 72, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 13, 86, 250, 254, 254, 254, 254, 217, 246, 151, 32, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 16, 179, 254, 254, 254, 254, 254, 254, 254, 254, 254, 231, 54, 15, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 72, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 104, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 61, 191, 254, 254, 254, 254, 254, 109, 83, 199, 254, 254, 254, 254, 243, 85, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 172, 254, 254, 254, 202, 147, 147, 45, 0, 11, 29, 200, 254, 254, 254, 171, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 174, 254, 254, 89, 67, 0, 0, 0, 0, 0, 0, 128, 252, 254, 254, 212, 76, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 47, 254, 254, 254, 29, 0, 0, 0, 0, 0, 0, 0, 0, 83, 254, 254, 254, 153, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 80, 254, 254, 240, 24, 0, 0, 0, 0, 0, 0, 0, 0, 25, 240, 254, 254, 153, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 64, 254, 254, 186, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 166, 254, 254, 224, 12, 0, 0, 0, 0, 0, 0, 0, 0, 14, 232, 254, 254, 254, 29, 0, 0, 0, 0, 0, 0, 0, 0, 0, 75, 254, 254, 254, 17, 0, 0, 0, 0, 0, 0, 0, 0, 18, 254, 254, 254, 254, 29, 0, 0, 0, 0, 0, 0, 0, 0, 0, 48, 254, 254, 254, 17, 0, 0, 0, 0, 0, 0, 0, 0, 2, 163, 254, 254, 254, 29, 0, 0, 0, 0, 0, 0, 0, 0, 0, 48, 254, 254, 254, 17, 0, 0, 0, 0, 0, 0, 0, 0, 0, 94, 254, 254, 254, 200, 12, 0, 0, 0, 0, 0, 0, 0, 16, 209, 254, 254, 150, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 15, 206, 254, 254, 254, 202, 66, 0, 0, 0, 0, 0, 21, 161, 254, 254, 245, 31, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 60, 212, 254, 254, 254, 194, 48, 48, 34, 41, 48, 209, 254, 254, 254, 171, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 86, 243, 254, 254, 254, 254, 254, 233, 243, 254, 254, 254, 254, 254, 86, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 114, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 239, 86, 11, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 13, 182, 254, 254, 254, 254, 254, 254, 254, 254, 243, 70, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8, 76, 146, 254, 255, 254, 255, 146, 19, 15, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
		}));
		cout << " 1 " << endl;
		printConf(net.predict(vector<double> {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 188, 255, 94, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 191, 250, 253, 93, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 123, 248, 253, 167, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 80, 247, 253, 208, 13, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 29, 207, 253, 235, 77, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 54, 209, 253, 253, 88, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 93, 254, 253, 238, 170, 17, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 23, 210, 254, 253, 159, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 16, 209, 253, 254, 240, 81, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 27, 253, 253, 254, 13, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 20, 206, 254, 254, 198, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 168, 253, 253, 196, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 20, 203, 253, 248, 76, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 22, 188, 253, 245, 93, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 103, 253, 253, 191, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 89, 240, 253, 195, 25, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 15, 220, 253, 253, 80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 94, 253, 253, 253, 94, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 89, 251, 253, 250, 131, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 214, 218, 95, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
		}));
		cout << "  2 " << endl;
		printConf(net.predict(vector<double>{
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 39, 91, 91, 91, 91, 91, 191, 255, 142, 91, 23, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 23, 211, 253, 253, 253, 253, 253, 253, 253, 253, 253, 181, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 180, 253, 253, 253, 253, 253, 253, 253, 253, 253, 253, 228, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 180, 253, 253, 253, 253, 253, 253, 253, 253, 253, 253, 228, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 101, 253, 253, 253, 253, 253, 253, 253, 253, 253, 253, 228, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 14, 224, 253, 253, 211, 114, 96, 253, 253, 253, 253, 228, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 48, 204, 114, 18, 0, 156, 253, 253, 253, 253, 228, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 15, 0, 0, 0, 230, 253, 253, 253, 253, 185, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 31, 156, 244, 253, 253, 253, 192, 25, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 209, 253, 253, 253, 253, 245, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5, 215, 253, 253, 253, 245, 130, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 124, 253, 253, 253, 253, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 41, 220, 253, 253, 253, 238, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 49, 222, 253, 253, 253, 253, 98, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 107, 253, 253, 253, 253, 210, 35, 0, 0, 0, 5, 42, 42, 42, 42, 18, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 107, 253, 253, 253, 253, 253, 178, 131, 131, 131, 143, 253, 253, 253, 253, 182, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 83, 240, 253, 253, 253, 253, 253, 253, 253, 253, 253, 253, 253, 253, 240, 195, 12, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 197, 253, 253, 253, 253, 253, 253, 253, 253, 253, 253, 229, 106, 82, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 33, 179, 241, 253, 253, 253, 253, 253, 253, 246, 179, 44, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 75, 89, 195, 89, 89, 89, 89, 81, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
		}));
		print(net.predict(vector<double>{
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 39, 91, 91, 91, 91, 91, 191, 255, 142, 91, 23, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 23, 211, 253, 253, 253, 253, 253, 253, 253, 253, 253, 181, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 180, 253, 253, 253, 253, 253, 253, 253, 253, 253, 253, 228, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 180, 253, 253, 253, 253, 253, 253, 253, 253, 253, 253, 228, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 101, 253, 253, 253, 253, 253, 253, 253, 253, 253, 253, 228, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 14, 224, 253, 253, 211, 114, 96, 253, 253, 253, 253, 228, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 48, 204, 114, 18, 0, 156, 253, 253, 253, 253, 228, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 15, 0, 0, 0, 230, 253, 253, 253, 253, 185, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 31, 156, 244, 253, 253, 253, 192, 25, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 209, 253, 253, 253, 253, 245, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5, 215, 253, 253, 253, 245, 130, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 124, 253, 253, 253, 253, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 41, 220, 253, 253, 253, 238, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 49, 222, 253, 253, 253, 253, 98, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 107, 253, 253, 253, 253, 210, 35, 0, 0, 0, 5, 42, 42, 42, 42, 18, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 107, 253, 253, 253, 253, 253, 178, 131, 131, 131, 143, 253, 253, 253, 253, 182, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 83, 240, 253, 253, 253, 253, 253, 253, 253, 253, 253, 253, 253, 253, 240, 195, 12, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 197, 253, 253, 253, 253, 253, 253, 253, 253, 253, 253, 229, 106, 82, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 33, 179, 241, 253, 253, 253, 253, 253, 253, 246, 179, 44, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 75, 89, 195, 89, 89, 89, 89, 81, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
		}));
	}
}

void xorTest() {


	jANN net(vector<int> {2, 15, 1});

	net.addTrainingData(vector<double> {0, 0}, vector<double> {1});
	net.addTrainingData(vector<double> {0, 1}, vector<double> {0});
	net.addTrainingData(vector<double> {1, 0}, vector<double> {0});
	net.addTrainingData(vector<double> {1, 1}, vector<double> {1});

	int train = 0;
	while (train != -1) {
		cin >> train;
		net.train(train);

		print(net.predict(vector<double> {0, 0}));
		print(net.predict(vector<double> {0, 1}));
		print(net.predict(vector<double> {1, 0}));
		print(net.predict(vector<double> {1, 1}));


	}
}
}
using namespace testclass;
