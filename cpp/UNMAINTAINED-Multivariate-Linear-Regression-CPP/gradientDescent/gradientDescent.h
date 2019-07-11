#pragma once
#ifndef gradientDescent_H
#define gradientDescent_H
#include "stdafx.h"
#include <vector>

using namespace std;

class gradientDescent {

	double learningRate = 0.003;
	double momentumeRate = 0.003;
	double regularizationConst = .005;
	int features;
	bool regularizationOn = true;

	
	std::vector<std::vector<double>> trainingSet;
	std::vector<double> outputSet;
	std::vector<double> constants;

public:
	gradientDescent(int features);
	void train();
	void train(int i);
	void addTrainingData(vector<double> data, double output);
	double evaluate(vector<double> data);

	vector<double> getConstants(); 
private: 
	void updateWeights();
	double HypothesisTheta(int i);
	double regularization(int j);
	void costFunction(int i, int j);
	double x(int i, int j);
	double y(int i);
	double lr() { return learningRate; }
	double r(int j) { return regularization(j); }
};


#endif