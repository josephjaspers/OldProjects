#pragma once
#ifndef jRNN_h
#define jRNN_h
#include "Matrices.h"
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;
using namespace Matrices;
class jANN {
	const double e = 2.71828182846;
	Vector* z;
	Vector* a;
	Vector* d;
	Vector* b;
	Vector* bM;
	Matrix* w;
	Matrix* m;

	int layers;
	int hiddenLayers;

	vector<int> networkStruct;

	double lr = .3;
	double mr = .01;

	vector<Vector> inputSet;
	vector<Vector> outputSet;


public:
	//Constructor
	jANN(vector<int> structure);
	jANN() {};
	~jANN();
	//Training Aspects 
	void addTrainingData(const vector<double>& inputSet, const vector<double>& outpuSeT);
	void train();
	void train(int i);
	void train(vector<double>& input, vector<double> & output);
	//predict
	vector<double> predict(const vector<double>& inputdata);
	Vector hD(Vector z);
	//save/read
	void read(ifstream & is);
	void write(ofstream& os);
private: 
	void forwardPropagation(Vector& input);
	void backwardPropagation(Vector& output);
	void forwardPropagation(vector<double>& input);
	void backwardPropagation(vector<double>& output);
	void updateWeights();


	Vector& g(Vector& z);
	Vector sig(Vector z);
	Vector gD(Vector z);

	Vector & h(Vector & z);

	Vector tanh(Vector z);

};
#endif