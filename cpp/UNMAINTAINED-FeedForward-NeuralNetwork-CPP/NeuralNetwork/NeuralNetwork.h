#include "stdafx.h"
#pragma once 
#ifndef NeuralNetwork_h
#define NeuralNetwork_h
#include "Matrix.h"
#include <iostream>
#include <cstdlib>

class NeuralNetwork {
	double const E = 2.718281828;

	vector<Matrix> trainingData;
	vector<Matrix> outputData;

	vector<Matrix> activation = vector<Matrix>(0);
	vector<Matrix> bias = vector<Matrix>(0);
	vector<Matrix> delta = vector<Matrix>(0);
	vector<Matrix> zeta = vector<Matrix>(0);
	vector<Matrix> momentum = vector<Matrix>(0);
	vector<Matrix> weights = vector<Matrix>(0);

	vector<Matrix> biasMomentum = vector<Matrix>(0);

	int inputs;
	int outputs;
	int hiddenFeatures;
	int hiddenLayers;
	int layers;

	double learningRate = 0.3;
	double momentumRate = 0.03;

public:
	NeuralNetwork(int input, int hiddenLayers, int hiddenFeatures, int outputs);
	void printNetwork();
	void setWeight(int layer, int from, int to, double weight);
	vector<double> predict(vector<double> data);

	void setLearningRate(double lr) { learningRate = lr; }
	void setMomentumRate(double m) { momentumRate = m; }
	void addTrainingData(const vector<double>& data, vector<double> outputData);
	void train();
	void train(int iters);

private:
	void forwardPropagation(const Matrix& data);
	void setBiasPropogation();
	void backwardPropagation(const Matrix& oData);
	void updateWeights();

	void generateNetwork();
	void initializeMatrices(int inputs, int connections);


	Matrix& a(int i) { return activation[i]; }
	Matrix& d(int i) { return delta[i]; }
	Matrix& z(int i) { return zeta[i]; }
	Matrix& b(int i) { return bias[i]; }
	Matrix& m(int i) { return momentum[i]; }
	Matrix& w(int i) { return weights[i]; }
	Matrix& bM(int i) { return biasMomentum[i]; }


};
#endif