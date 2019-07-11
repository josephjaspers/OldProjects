// jANN.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "jANN.h"

/*
All methods of the algorthim - namely Forwardpropgation, backwardPropagation, and update weights 
utilize the optimized Matrix methods of the Matrices.lib 

Commented out is the mathematical notation of the algorithm.
The commented out code variants can be used interchangebly with the optimized variants.
The Matrix class given supports the usage of the utilized operators. 

*/
jANN::jANN(vector<int> structure)
{
	layers = structure.size();
	networkStruct = structure;
	a = new Vector[layers];
	d = new Vector[layers];
	b = new Vector[layers];
	bM = new Vector[layers];
	w = new Matrix[layers];
	m = new Matrix[layers];

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
	}
	a[layers - 1] = Vector(structure.back());
	d[layers - 1] = Vector(structure.back());
	b[layers - 1] = Vector(1); //Matrix not used
	bM[layers - 1] = Vector(1); //not used
	w[layers - 1] = Matrix(1, 1); //not used
	m[layers - 1] = Matrix(1, 1);//not used
}

jANN::~jANN()
{
	delete[] a;
	delete[] d;
	delete[] b;
	delete[] bM;
	delete[] w;
	delete[] m;
}

void jANN::addTrainingData(const vector<double>& i, const vector<double>& o)
{
	if (i.size() != networkStruct[0]) {
		throw out_of_range("Except");
	}
	inputSet.push_back(Vector(i));
	outputSet.push_back(Vector(o));
}

void jANN::train()
{
	for (int i = 0; i < inputSet.size(); ++i) {
		forwardPropagation(inputSet[i]);
		backwardPropagation(outputSet[i]);
		updateWeights();
	}
}

void jANN::train(int i)
{
	while (i > 0) {
		train();
		--i;
	}
}

void jANN::train(vector<double>& input, vector<double>& output)
{
	forwardPropagation(Vector(input));
	backwardPropagation(Vector(output));
	updateWeights();
}

vector<double> jANN::predict(const vector<double>& inputdata)
{
	forwardPropagation(Vector(inputdata));
	return a[layers - 1].getCpyVect();
}


void jANN::forwardPropagation(Vector & input)
{
	a[0] = input; //cpy
	for (int i = 1; i < layers; ++i) {
		//a[i] = g(w[i - 1] * a[i - 1] + b);
		dot(a[i], w[i - 1], a[i - 1]);
		add(a[i], a[i], b[i - 1]);
		g(a[i]); //sigmoidFunction
	}
}
void jANN::backwardPropagation(Vector & output)
{
	//d[layers - 1] = a[layers - 1] - output;
	sub(d[layers - 1], a[layers - 1], output);
	for (int l = layers - 2; l > 0; --l) {
		//d[l] = w[l].T() * d[l+1] & gD(a[l]); // * = dot product | & = pointwise multiplication
		dotTranspose(d[l], w[l], d[l + 1]);
		d[l] &= gD(a[l]);
	}
}
void jANN::forwardPropagation(vector<double>& input)
{
	a[0] = input; //Technically undefined behavior, but will function on Windows Machines, 
				  //-- will overload operators eventually
	for (int i = 1; i < layers; ++i) {
		//a[i] = g(w[i-1]*a[i-1] +b)
		dot(a[i], w[i - 1], a[i - 1]);
		add(a[i], a[i], b[i - 1]);
		g(a[i]); //sigmoidFunction
	}
}

void jANN::backwardPropagation(vector<double>& output)
{
	sub(d[layers - 1], a[layers - 1], output);
	for (int l = layers - 2; l > 0; --l) {
		//d[l] = w[l].t * d[l+1] & gd(a[l])
		dotTranspose(d[l], w[l], d[l + 1]);
		mult(d[l], d[l], gD(a[l]));
	}
}

void jANN::updateWeights() {
	for (int l = 0; l < layers - 1; ++l) {
		w[l] -= ((d[l + 1] * a[l]) & lr);// +(m[l] & mr);
		b[l] -= ((d[l + 1]) & lr);// +(bM[l] & mr);
	
	//	m[l] = (d[l + 1] * a[l]);
	//	bM[l] = d[l + 1];
	}
}
Vector & jANN::g(Vector & z)
{
	//sigmoid function  1 / 1 + e^-x
	for (int i = 0; i < z.size(); ++i) {
		z[i] = 1 / (1 + pow(e, -z[i]));// sigmoid
		//z[i] = std::tanh(z[i]); //tanh
		//z[i] = (pow(e, z[i]) - pow(e, -z[i])) / (pow(e, z[i]) + pow(e, -z[i]));
	}
	return z;
}

Vector jANN::gD(Vector z)
{
	//derivative of sigmoid function (post crush). Source: Andrew Ng (coursera) Machines Learning Standford
	for (int i = 0; i < z.size(); ++i) {
		z[i] *= (1 - z[i]); //sigmoid
		//z[i] = (1 - pow(z[i], 2)); //tanh
	}
	return z;
}

void jANN::read(ifstream& is)
{
//does not save training set
	is >> layers;
	networkStruct = vector<int>(0);
	for (int l = 0; l < layers; ++l) {
		int nodes;
		is >> nodes;
		networkStruct.push_back(nodes);
	}
	is >> lr;
	is >> mr;
	delete[] a, b, bM, d, m, w;
	a = new Vector[layers];
	b = new Vector[layers];
	bM = new Vector[layers];
	d = new Vector[layers];
	m = new Matrix[layers];
	w = new Matrix[layers];
	for (int i = 0; i < layers; ++i) {
		a[i] = Vector::read(is);
		b[i] = Vector::read(is);
		bM[i] = Vector::read(is);
		d[i] = Vector::read(is);
		m[i] = Matrix::read(is);
		w[i] = Matrix::read(is);
	}
}
void jANN::write(ofstream & o)
{
	//does not save training set
	o << layers << ' ';
	for (int i = 0; i < networkStruct.size(); ++i) {
		o << networkStruct[i] << ' ';
	}
	o << lr << ' ';
	o << mr << ' ';

	for (int l = 0; l < layers; ++l) { //alphabetical
		a[l].write(o);
		b[l].write(o);
		bM[l].write(o);
		d[l].write(o);
		m[l].write(o);
		w[l].write(o);
	}
}