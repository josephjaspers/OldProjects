#include "stdafx.h"
#include "NeuralNetwork.h"
#include <vector>
#include "Matrix.h"
#include <iostream>

Matrix g(Matrix z) { //sigmoidFunction
	double E = 2.718281828;
	Matrix gZ = Matrix(z.length(), z.width());

	for (int l = 0; l < z.length(); ++l) {
		for (int w = 0; w < z.width(); ++w) {
			gZ(l, w) = 1 / (1 + pow(E, -z(l, w)));
		}
	}
	return gZ;
}
Matrix gD(Matrix gZ) {
	double E = 2.718281828;

	for (int l = 0; l < gZ.length(); ++l) {
		for (int w = 0; w < gZ.width(); ++w) {
			gZ(l, w) *= (1 - gZ(l, w));
		}
	}
	return gZ;
}
int randNum(int min, int max)
{
	return rand() % max + min;
}
Matrix& randomize(Matrix &m) {
	for (int i = 0; i < m.size(); ++i) {
		m[i] = randNum(-2, 2);
	}
	return m;
}
NeuralNetwork::NeuralNetwork(int i, int hL, int hF, int o) {
	if (hL < 1 || i < 1 || hF < 1 || o < 1) {
		throw std::exception("minimum of 1 layer and 1 input / output and 1 hiddenfeatures");
	}
	NeuralNetwork::inputs = i;
	NeuralNetwork::hiddenFeatures = hF;
	NeuralNetwork::hiddenLayers = hL;
	NeuralNetwork::outputs = o;
	layers = hL + 2;

	generateNetwork();
}
void NeuralNetwork::generateNetwork() {
	//input layer
	initializeMatrices(inputs, hiddenFeatures);
	//for each hiddenLayer - 1
	for (int i = 0; i < hiddenLayers - 1; ++i) {
		initializeMatrices(hiddenFeatures, hiddenFeatures);
	}
	//for last hiddenLayer (or if 1 the only hiddenLayer)
	initializeMatrices(hiddenFeatures, outputs);
	//for each output layer
	initializeMatrices(outputs, 0);
}
void NeuralNetwork::initializeMatrices(int inputs, int connections) {
	activation.push_back(Matrix(inputs));
	delta.push_back(Matrix(inputs));
	zeta.push_back(Matrix(inputs));
	bias.push_back(randomize(Matrix(connections)));
	biasMomentum.push_back(Matrix(connections));
	weights.push_back(randomize(Matrix(connections, inputs)));
	momentum.push_back(Matrix(connections, inputs));
}
void NeuralNetwork::setWeight(int layer, int from, int to, double weight) {
	w(layer)(to, from) = weight;
}
void NeuralNetwork::forwardPropagation(const Matrix& data) {
	//setBiasPropogation();
	a(0) = data; //1 to offset for bias unit

	for (int i = 1; i < layers; ++i) {
		z(i) = (w(i - 1) * a(i - 1) + b(i - 1)); // (set(1, -- is a length offset(avoid erasing bias)
		a(i) = g(z(i));
	}
}
void NeuralNetwork::setBiasPropogation() {
	for (int i = 0; i < activation.size(); ++i) {
		a(i)[0] = 1;
	}
}
void NeuralNetwork::backwardPropagation(const Matrix& output) {
	d(layers - 1) = a(layers - 1) - Matrix(output);
	for (int i = layers - 2; i > -1; --i) {
		d(i) = (w(i).T() * d(i + 1)).x(gD(a(i))); //(.x is multiply while * is dotproduct
	}		//cpy(n) returns a copy of the matrix offset by n (ignores n rows)
}
void NeuralNetwork::updateWeights() {
	// the operator () (int l, int w) returns a double reference at that position in the matrix
	// thet operator [] (int n) returns the nth double (reference) in the matrix (useful for vectors) 
	for (int l = 0; l < layers - 1; ++l) {
		for (int i = 0; i < d(l + 1).length(); ++i) {
			for (int j = 0; j < a(l).length(); ++j) {
				w(l)(i, j) -= (d(l + 1)[i] * a(l)[j]) * learningRate + m(l)(i, j);
				m(l)(i, j) = (d(l + 1)[i] * a(l)[j]) * momentumRate;
			}
		}
	}
	for (int l = 0; l < layers - 1; ++l) {
		for (int i = 0; i < d(l + 1).length(); ++i) {
			b(l)[i] -= d(l + 1)[i] * learningRate + bM(l)[i];
			bM(l)[i] = d(l + 1)[i] * momentumRate;
		}
	}
}
std::vector<double> NeuralNetwork::predict(std::vector<double> data) {
	if (data.size() != inputs) {
		throw std::exception("data must have the same number of outputs");
	}
	forwardPropagation(data);

	vector<double> output = a(layers - 1).getColumn(0).getCpyVect();
	return output;
}
void NeuralNetwork::printNetwork() {
	std::cout.precision(5);
	for (int i = 0; i < weights.size(); ++i) {
		std::cout << "------activation at ------" << i << std::endl;
		a(i).print();
		std::cout << "------z activation at -----" << i << std::endl;
		z(i).print();
		std::cout << "Layer -----------" << i << endl;
		std::cout << "Weights" << std::endl;
		w(i).print();
		std::cout << "delta delta " << std::endl;
		d(i).print();
	}
}
void NeuralNetwork::addTrainingData(const vector<double>& data, vector<double> output) {
	if (data.size() != inputs) {
		throw std::exception("data length feature size mismatch");
	}
	if (output.size() != outputs) {
		throw std::exception("outputData must match the number of outputs");
	}
	trainingData.push_back(data);
	outputData.push_back(output);
}
void NeuralNetwork::train() {
	for (int i = 0; i < trainingData.size(); ++i) {
		forwardPropagation(trainingData[i]);
		backwardPropagation(outputData[i]);
		updateWeights();
	}
}
void NeuralNetwork::train(int iter) {
	while (iter > 0) {
		train();
		iter--;
	}
}
