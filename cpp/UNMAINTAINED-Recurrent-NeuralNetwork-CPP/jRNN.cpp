// jRNN.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "jRNN.h"

/*
The purpose of this RNN is to generate clear code. I have attempted generate code that is as closely to as possible as the original
algorithms for the purpose of clarity.

Commented out are mathematical code variants. All code variants utilize overloaded operators in the given Matrix library and may be used interchangeably as is. 


Current implemetation uses a variant of BPTT and updates the weights at each timestamp. 
This is done for the sake of clarity. 

To implement standard BPTT simply create a copy of the weights to calculate the gradients with BPTT and backpropagation and then call update weights as normal.
*/
jRNN::jRNN(vector<int> structure)
{
	layers = structure.size();
	networkStruct = structure;
	a = vector<Vector>(layers);
	d = new Vector[layers];
	b = new Vector[layers - 1];
	bM = new Vector[layers - 1];
	w = new Matrix[layers - 1];
	m = new Matrix[layers - 1];
	r = new Matrix[layers - 2];

	for (int i = 0; i < structure.size() - 1; ++i) {
		a[i] = Vector(structure[i]);
		d[i] = Vector(structure[i]);
		b[i] = Vector(structure[i + 1]);
		randomize(b[i], -4, 4);
		bM[i] = Vector(structure[i + 1]);
		w[i] = Matrix(structure[i + 1], structure[i]);
		randomize(w[i], -4, 4);
		m[i] = Matrix(structure[i + 1], structure[i]);
		randomize(m[i], -4, 4);
		if (i != structure.size() - 2) {
			r[i] = Matrix(structure[i + 1], structure[i + 1]);
			randomize(r[i], -4, 4);
		}
	}
	a[layers - 1] = Vector(structure.back());
	d[layers - 1] = Vector(structure.back());

}

jRNN::~jRNN()
{
	delete[] d;
	delete[] b;
	delete[] bM;
	delete[] w;
	delete[] m;
	delete[] r;
}

void jRNN::addTrainingData(const vector<double>& i, const vector<double>& o)
{
	inputSet.push_back(vector<Vector> { Vector(i) });
	outputSet.push_back(Vector(o));
}
void jRNN::addTrainingData(const vector<vector<double>>& inputData, const vector<double>& o)
{
	vector<Vector> iData(inputData.size());
	for (int i = 0; i < inputData.size(); ++i) {
		iData[i] = Vector(inputData[i]);
	}
	inputSet.push_back(iData);
	outputSet.push_back(Vector(o));
}

void jRNN::train()
{
	for (int i = 0; i < inputSet.size(); ++i) {
		bpA.clear();			//Clear all activations from the last training example
		clearActivations();	    //Clear activations from the last time stamp
		bpA.push_back(a);		//push back an activation set --> this set will only be of 0's. 

		for (int j = 0; j < inputSet[i].size(); ++j) {
			forwardPropagation(inputSet[i][j]);
			bpA.push_back(a);
		}
		backwardPropagation(outputSet[i]); //calculates the "Feed forward" error 
		updateWeights(); 
		BPTT(); //BPTT will calculate the recurrent error
	}
}
void jRNN::train(int i)
{
	//Enables training over a batch of the data set multiple times.
	while (i > 0) {
		train();
		--i;
	}
}
void jRNN::train(vector<double>& input, vector<double>& output)
{
	//Train an input set with only 1 element in the sequence
	clearActivations();
	forwardPropagation(Vector(input));
	backwardPropagation(Vector(output));
	updateWeights();
}
void jRNN::train(vector<vector<double>>& input, vector<double>& output) {
	clearActivations();
	bpA.clear();

	bpA.push_back(a);
	for (int i = 0; i < input.size(); ++i) {
		forwardPropagation(Vector(input[i]));
		bpA.push_back(a);
	}
	backwardPropagation(Vector(output));
	updateWeights();
	BPTT();
}
vector<double> jRNN::predict(const vector<double>& inputdata)
{
	clearActivations();
	forwardPropagation(Vector(inputdata));
	return a[layers - 1].getCpyVect();
}
vector<double> jRNN::predict(const vector<vector<double>>& inputdata)
{
	clearActivations();
	for (int i = 0; i < inputdata.size(); ++i) {
		forwardPropagation(Vector(inputdata[i]));
	}
	return a[layers - 1].getCpyVect();
}

void jRNN::forwardPropagation(Vector & input)
{
	//*Only the hidden layers are recurrent* 
	a[0] = input; //cpy
	for (int i = 1; i < layers - 1; ++i) {
		a[i] = (r[i - 1] * a[i]) + (w[i - 1] * a[i - 1]) + b[i - 1];
		g(a[i]);
	}
	a[layers - 1] = w[layers - 2] * a[layers - 2] + b[layers - 2];
	g(a[layers - 1]); //sigmoidFunction
}
void jRNN::backwardPropagation(Vector & output)
{
	//Equivalent to a feed forward backpropagation
	sub(d[layers - 1], a[layers - 1], output);
	for (int l = layers - 2; l > 0; --l) {
		//Math notation - d[l] = w[l].T() * d[l + 1] & gD(A(l));
		d[l] = (dotTranspose(w[l], d[l + 1]) &= gD(A(l)));
	}
}
void jRNN::backwardPropagation() {
	for (int l = layers - 3; l > -1; --l) {
		//calculate the recurrent error 
		d[l + 1] = (dotTranspose(r[l], d[l + 1]) & gD(Am(l + 1)));
		//Get the gradients
		r[l] -= ((d[l + 1] * Am(l + 1)) & (lr));
		w[l] -= ((d[l + 1] * A(l)) & (lr));
	}
}
void jRNN::BPTT() {
	bpA.pop_back();
	while (bpA.size() > 1) {
		backwardPropagation();
		bpA.pop_back();
	}
}

void jRNN::updateWeights() {
	for (int l = 0; l < layers - 1; ++l) {
		sub(w[l], w[l], dot(d[l + 1], A(l)) & lr);
		sub(b[l], b[l], (d[l + 1] & lr));

		//Input and Output Layers are non recurrent. --This avoids attempting to update recurrent weights for the output layer
		if (l != layers - 2) {
			sub(r[l], r[l], dot(d[l + 1], Am(l + 1)) & lr);
		}
	}
}
void jRNN::clearActivations() {
	//Erases all activations. This method may need to be deleted for certain types of learning problems. 
	//Namely, sequences that are dependent upon prior sequences.

	for (int i = 0; i < a.size(); ++i) {
		for (int j = 0; j < a[i].size(); ++j) {
			a[i][j] = 0;
		}
	}
}
Vector & jRNN::g(Vector & z)
{
	//sigmoid function is used opposed to tanH as the derivative is more easily used as we do not need to store the inputs, (only the activations)
	//sigmoid function  1 / 1 + e^-x
	for (int i = 0; i < z.size(); ++i) {
		z[i] = 1 / (1 + pow(E, -z[i]));
	}
	return z;
}
Vector jRNN::gD(Vector z)
{
	//derivative of sigmoid function (post crush). Source: Andrew Ng (coursera) Machines Learning Standford
	for (int i = 0; i < z.size(); ++i) {
		z[i] *= (1 - z[i]);
	}
	return z;
}

void jRNN::read(ifstream& is)
{
	//Read a neural network -- does not save/read the trainingset.
	is >> layers;
	networkStruct = vector<int>(0);
	for (int l = 0; l < layers; ++l) {
		int nodes;
		is >> nodes;
		networkStruct.push_back(nodes);
	}
	is >> lr;
	is >> mr;
	delete[] b, bM, d, m, w;
	a = vector<Vector>(layers);
	b = new Vector[layers];
	bM = new Vector[layers];
	d = new Vector[layers];
	m = new Matrix[layers];
	w = new Matrix[layers];
	for (int i = 0; i < layers - 1; ++i) {
		a[i] = Vector::read(is);
		b[i] = Vector::read(is);
		bM[i] = Vector::read(is);
		d[i] = Vector::read(is);
		m[i] = Matrix::read(is);
		w[i] = Matrix::read(is);
	}
	a[layers - 1] = Vector::read(is);
	b[layers - 1] = Vector::read(is);
}
void jRNN::write(ofstream & o)
{
	//write a neuralnetwork does not save the training sets.
	o << layers << ' ';
	for (int i = 0; i < networkStruct.size(); ++i) {
		o << networkStruct[i] << ' ';
	}
	o << lr << ' ';
	o << mr << ' ';

	for (int l = 0; l < layers - 1; ++l) { //alphabetical
		a[l].write(o);
		b[l].write(o);
		bM[l].write(o);
		d[l].write(o);
		m[l].write(o);
		w[l].write(o);
	}
	a[layers - 1].write(o);
	b[layers - 1].write(o);
}