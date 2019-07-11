#include "stdafx.h"
#include "ANN.h"

Matrix& ANN::g(Matrix& z) { //sigmoidFunction
	double E = 2.718281828;

	for (int i = 0; i < z.size(); ++i) {
		z[i] = 1 / (1 + pow(E, -z[i]));
	}
	return z;
}
Matrix& ANN::gD(Matrix& gZ) {
	for (int i = 0; i < gZ.size(); ++i) {
		gZ[i] *= (1 - gZ[i]);
	}
	return gZ;
}
int randNum(int min, int max)
{
	int neg = rand() % 2;
	if (neg == 0) {
		neg = -1;
	}
	return neg * (rand() % max + min);

}
Matrix& randomize(Matrix &m) {
	for (int i = 0; i < m.size(); ++i) {
		m[i] = randNum(-4, 4);
	}
	return m;
}
ANN::ANN(int i, int hL, int hF, int o) {
	if (hL < 1 || i < 1 || hF < 1 || o < 1) {
		throw std::exception("minimum of 1 layer and 1 input / output and 1 hiddenfeatures");
	}
	ANN::inputs = i;
	ANN::hiddenFeatures = hF;
	ANN::hiddenLayers = hL;
	ANN::outputs = o;
	layers = hL + 2;

	generateNetwork();
}
void ANN::generateNetwork() {
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
void ANN::initializeMatrices(int inputs, int connections) {
	activation.push_back(unique_ptr<Matrix>(new Matrix(inputs)));
	delta.push_back(unique_ptr<Matrix>(new Matrix(inputs)));
	bias.push_back(unique_ptr<Matrix>(new Matrix(connections)));
	randomize(*(bias.back()));
	biasMomentum.push_back(unique_ptr<Matrix>(new Matrix(connections)));
	weights.push_back(unique_ptr<Matrix>(new Matrix(connections, inputs)));
	randomize(*(weights.back()));
	momentum.push_back(unique_ptr<Matrix>(new Matrix(connections, inputs)));
}
void ANN::setWeight(int layer, int from, int to, double weight) {
	w(layer)(to, from) = weight;
}
void ANN::resetWeights()
{
	for (int i = 0; i < weights.size(); ++i) {
		randomize(*weights[i]);
		randomize(*momentum[i]);
	}
}
void ANN::forwardPropagation(const Matrix& data) {
	//optimized Code
	a(1) = g(*(w(0) * data) += b(0)); // (set(1, -- is a length offset(avoid erasing bias)
	a(1);
	for (int i = 2; i < layers; ++i) {
		a(i) = g(*(w(i - 1) * a(i - 1)) += b(i - 1)); // (set(1, -- is a length offset(avoid erasing bias)
	}

	//nice looking code
	//	a(0) = data;
	//	for (int i = 1; i < layers; ++i) {
	//		a(i) = g(w(i - 1) * a(i - 1) + b(i - 1)); // (set(1, -- is a length offset(avoid erasing bias)
	//	}
}
void ANN::backwardPropagation(const Matrix& output) {
	delta[layers - 1] = (a(layers - 1) - output);
	for (int i = layers - 2; i > 0; --i) {
		d(i) = *(w(i).T() * d(i + 1)) *= (gD(a(i))); //(.x is multiply while * is dotproduct
													//*= is a pointwise multiplyer *= is for slight performance increase
		w(i).T(); //(untranspose) This is required
	}
}

void ANN::updateWeights() {
	// the operator () (int l, int w) returns a double reference at that position in the matrix
	// thet operator [] (int n) returns the nth double (reference) in the matrix (useful for vectors) 
	for (int l = 0; l < layers - 1; ++l) {
		for (int i = 0; i < d(l + 1).length(); ++i) {
			for (int j = 0; j < a(l).length(); ++j) {

				//clean version 
				//w(l)(i, j) -= (d(l + 1)[i] * a(l)[j]) * learningRate + m(l)(i, j);
				//m(l)(i, j) = ((d(l + 1)[i] * a(l)[j]) + m(l)(i,j)) * momentumRate;

				//optimized version 
				double adj = d(l + 1)[i] * a(l)[j];
				w(l)(i, j) -= adj * learningRate + m(l)(i, j);
				m(l)(i, j) = adj + m(l)(i, j) * momentumRate;
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
std::vector<double> ANN::predict(std::vector<double> data) {
	if (data.size() != inputs) {
		throw std::exception("data must have the same number of outputs");
	}
	forwardPropagation(data);

	vector<double> output = a(layers - 1).getCpyVect();
	return output;
}
void ANN::printNetwork() {
	std::cout.precision(5);
	for (int i = 0; i < weights.size(); ++i) {
		std::cout << "------activation at ------" << i << std::endl;
		a(i).print();
		std::cout << "Layer -----------" << i << endl;
		std::cout << "Weights" << std::endl;
		w(i).print();
		std::cout << "delta delta " << std::endl;
		d(i).print();
	}
}
void ANN::addTrainingData(const vector<double>& data, const vector<double>& output) {
	if (data.size() != inputs) {
		throw std::exception("data length feature size mismatch");
	}
	if (output.size() != outputs) {
		throw std::exception("outputData must match the number of outputs");
	}
	trainingData.push_back(unique_ptr<Matrix>(new Matrix(data)));
	outputData.push_back(unique_ptr<Matrix>(new Matrix(output)));
}
void ANN::train() {

	for (int i = 0; i < trainingData.size(); ++i) {
		//cout << "training " << i << " of  " << trainingData.size() << endl;
		forwardPropagation(*trainingData[i]);
		backwardPropagation(*outputData[i]);
		updateWeights();
	}
}
void ANN::train(int iter) {
	while (iter > 0) {
		train();
		iter--;
	}
}
void ANN::train(const vector<double>& iData, const vector<double>& oData)
{
	forwardPropagation(Matrix(iData));
	backwardPropagation(Matrix(oData));
	updateWeights();
}