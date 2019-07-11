#include "stdafx.h"
#pragma once
#ifndef ANN_h
#define ANN_h
#include "Matrix.h"
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <ostream> 
#include <ctime>
#include <list>

class ANN {
	vector<unique_ptr<Matrix>> trainingData;
	vector<unique_ptr<Matrix>> outputData;

	vector<unique_ptr<Matrix>> activation = vector<unique_ptr<Matrix>>(0);
	vector<unique_ptr<Matrix>> bias = vector<unique_ptr<Matrix>>(0);
	vector<unique_ptr<Matrix>> delta = vector<unique_ptr<Matrix>>(0);
	vector<unique_ptr<Matrix>> momentum = vector<unique_ptr<Matrix>>(0);
	vector<unique_ptr<Matrix>> weights = vector<unique_ptr<Matrix>>(0);

	vector<unique_ptr<Matrix>> biasMomentum = vector<unique_ptr<Matrix>>(0);

	int inputs;
	int outputs;
	int hiddenFeatures;
	int hiddenLayers;
	int layers;

	double learningRate = .3;
	double momentumRate = 0.3;

public:
	Matrix & g(Matrix & z);
	Matrix & gD(Matrix & gZ);
	//constructor 
	ANN(int input, int hiddenLayers, int hiddenFeatures, int outputs);
	//print
	void printNetwork();
	//set weights
	void setWeight(int layer, int from, int to, double weight);
	//reset 
	void resetWeights();
	vector<double> predict(vector<double> data);
	//simple mutators
	void setLearningRate(double lr) { learningRate = lr; }
	void setMomentumRate(double m) { momentumRate = m; }
	int getTrainingSetSize() { return trainingData.size(); }
	void clearTrainingData() {
		trainingData.clear();
		outputData.clear();
	}
	//simple accessors
	double getLearningRate() { return learningRate; }
	double getMomentumnRate() { return momentumRate; }
	int getNumbInputs() { return inputs; }
	int getHiddenNodes() { return hiddenFeatures; }
	int getNumbOutputs() { return outputs; }
	//training methods
	void addTrainingData(const vector<double>& data, const vector<double>& outputData);
	void train();
	void train(int iters);
	void train(const vector<double>& iData, const vector<double>& oData);
	//read/write methods
	bool read(ifstream& i);
	void write(ofstream& o);
	void testRandom();

private:
	void forwardPropagation(const Matrix& data);
	void backwardPropagation(const Matrix& oData);
	void updateWeights();

	void generateNetwork();
	void initializeMatrices(int inputs, int connections);

	inline Matrix& a(int i) { return *activation[i]; }
	inline Matrix& d(int i) { return *delta[i]; }
	inline Matrix& b(int i) { return *bias[i]; }
	inline Matrix& m(int i) { return *momentum[i]; }
	inline Matrix& w(int i) { return *weights[i]; }
	inline Matrix& bM(int i) { return *biasMomentum[i]; }
};
#endif