#pragma once
#ifndef jRNN_h
#define jRNN_h
#include "Matrices.h"
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;
using namespace Matrices;
class jRNN {
	const double E = 2.7182818281828;

	vector<Vector> a;
	Vector* d;
	Vector* b;
	Vector* bM;
	Matrix* w;
	Matrix* r;
	Matrix* m;

	vector <vector<Vector>> bpA;

	int layers;

	vector<int> networkStruct;

	double lr = .3;
	double mr = .01;

	vector<vector<Vector>> inputSet;
	vector<Vector> outputSet;


public:
	//Constructor
	jRNN(vector<int> structure);
	jRNN() {};
	~jRNN();
	//Training Aspects 
	void addTrainingData(const vector<double>& inputSet, const vector<double>& outpuSet);
	void addTrainingData(const vector<vector<double>>& inputSet, const vector<double>& outputset);
	void train();
	void train(int i);
	void train(vector<double>& input, vector<double> & output);
	void train(vector<vector<double>>& input, vector<double> & output);

	//predict
	vector<double> predict(const vector<double>& inputdata);
	vector<double> predict(const vector<vector<double>>& inputData);
	//save/read
	void read(ifstream & is);
	void write(ofstream& os);

	double delta;
	double rDelta() {
		double t = delta;
		delta = 0;
		return t;
	}

private:
	void forwardPropagation(Vector& input);
	void backwardPropagation(Vector& output);
	void backwardPropagation();
	void BPTT();
	void updateWeights();


	void clearActivations();

	Vector& g(Vector& z);
	Vector gD(Vector z);

	Vector& A(int l) { return bpA.back()[l]; }
	Vector& Am(int l) { return bpA[bpA.size() - 1][l]; }

};
#endif