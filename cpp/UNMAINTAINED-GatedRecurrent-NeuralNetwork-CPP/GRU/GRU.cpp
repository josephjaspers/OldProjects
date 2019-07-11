// GRU.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Gru.h"

/*
The purpose of this RNN is to generate clear code. I have attempted generate code that is as closely to as possible as the original
algorithms for the purpose of clarity.

Commented out are mathematical code variants. All code variants utilize overloaded operators in the given Matrix library and may be used interchangeably as is.

Current implemetation uses untruncated BPTT
*/
GRU::GRU(vector<int> structure)
{
	layers = structure.size();
	networkStruct = structure;

	c = vector<Vector>(layers);
	dc = new Vector[layers];

	z = vector<Vector>(layers);
	dz = new Vector[layers];
	bz = new Vector[layers - 1];
	wz = new Matrix[layers - 1];
	rz = new Matrix[layers - 1];
	bz_GradientStorage = new Vector[layers - 1];
	wz_GradientStorage = new Matrix[layers - 1];
	rz_GradientStorage = new Matrix[layers - 1];

	f = vector<Vector>(layers);
	rf = new Matrix[layers - 1];
	wf = new Matrix[layers - 1];
	bf = new Vector[layers - 1];
	df = new Vector[layers];
	bf_GradientStorage = new Vector[layers - 1];
	wf_GradientStorage = new Matrix[layers - 1];
	rf_GradientStorage = new Matrix[layers - 1];

	for (int i = 0; i < structure.size() - 1; ++i) {
		c[i] = Vector(structure[i]);
		dc[i] = Vector(structure[i]);

		z[i] = Vector(structure[i]);
		dz[i] = Vector(structure[i]);
		bz[i] = Vector(structure[i + 1]);
		wz[i] = Matrix(structure[i + 1], structure[i]);
		rz[i] = Matrix(structure[i + 1], structure[i + 1]);
		randomize(bz[i], -4, 4);
		randomize(wz[i], -4, 4);
		randomize(rz[i], -4, 4);
		bz_GradientStorage[i] = Vector(structure[i + 1]);
		wz_GradientStorage[i] = Matrix(structure[i + 1], structure[i]);
		rz_GradientStorage[i] = Matrix(structure[i + 1], structure[i + 1]);

		f[i] = Vector(structure[i]);
		df[i] = Vector(structure[i]);
		bf[i] = Vector(structure[i + 1]);
		wf[i] = Matrix(structure[i + 1], structure[i]);
		rf[i] = Matrix(structure[i + 1], structure[i + 1]);
		randomize(bf[i], -4, 4);
		randomize(wf[i], -4, 4);
		randomize(rf[i], -4, 4);
		bf_GradientStorage[i] = Vector(structure[i + 1]);
		wf_GradientStorage[i] = Matrix(structure[i + 1], structure[i]);
		rf_GradientStorage[i] = Matrix(structure[i + 1], structure[i + 1]);
	}
	c[layers - 1] = Vector(structure.back());
	dc[layers - 1] = Vector(structure.back());

	z[layers - 1] = Vector(structure.back());
	dz[layers - 1] = Vector(structure.back());
	f[layers - 1] = Vector(structure.back());
	df[layers - 1] = Vector(structure.back());
}
GRU::~GRU()
{
	delete[] dc;

	delete[] dz;
	delete[] bz;
	delete[] wz;
	delete[] rz;
	delete[] bz_GradientStorage;
	delete[] wz_GradientStorage;
	delete[] rz_GradientStorage;

	delete[] df;
	delete[] bf;
	delete[] wf;
	delete[] rf;
	delete[] bf_GradientStorage;
	delete[] wf_GradientStorage;
	delete[] rf_GradientStorage;
}
void GRU::addTrainingData(const vector<double>& i, const vector<double>& o)
{
	inputSet.push_back(vector<Vector> { Vector(i) });
	outputSet.push_back(Vector(o));
}
void GRU::addTrainingData(const vector<vector<double>>& inputData, const vector<double>& o)
{
	vector<Vector> iData(inputData.size());
	for (int i = 0; i < inputData.size(); ++i) {
		iData[i] = Vector(inputData[i]);
	}
	inputSet.push_back(iData);
	outputSet.push_back(Vector(o));
}
void GRU::train()
{
	for (int d = 0; d < inputSet.size(); ++d) {
		initializeGradientStorage();
		for (int j = 0; j < inputSet[d].size(); ++j) {
			bpZ.push_back(z);
			bpF.push_back(f);
			bpC.push_back(c);

			forwardPropagation(inputSet[d][j]);
		}
		backwardPropagation(outputSet[d]); //calculates the "Feed forward" error 
		updateWeights();
		BPTT(); //BPTT will calculate the recurrent error
		SetWeightsToGradientSums();
	}
}
void GRU::train(int i)
{
	//Enables training over z batch of the data set multiple times.
	while (i > 0) {
		train();
		--i;
	}
}
vector<double> GRU::predict(const vector<double>& inputdata)
{
	//clearActivations();
	return forwardPropagation(Vector(inputdata)).getCpyVect();
}
vector<double> GRU::predict(const vector<vector<double>>& inputdata)
{
	//clearActivations();
	for (int i = 0; i < inputdata.size() - 1; ++i) {
		forwardPropagation(Vector(inputdata[i]));
	}
	return forwardPropagation(Vector(inputdata.back())).getCpyVect();
}
Vector& GRU::forwardPropagation(Vector & input)
{
	c[0] = input;
	for (int l = 1; l < layers; ++l) {
		z[l] = rz[l - 1] * c[l] + wz[l - 1] * c[l - 1] + bz[l - 1];
		f[l] = rf[l - 1] * c[l] + wf[l - 1] * c[l - 1] + bf[l - 1];
		g(z[l]);
		g(f[l]);
		c[l] &= f[l];
		c[l] += z[l];
	}
	return c[layers - 1];
}
void GRU::backwardPropagation(Vector & output)
{
	dc[layers - 1] = c[layers - 1] - output;
	df[layers - 1] = dc[layers - 1] & Ct(layers - 1);
	dz[layers - 1] = dc[layers - 1];
	for (int l = layers - 2; l > 0; --l) {
		dc[l] = wz[l].T() * dz[l + 1] + wf[l].T() * df[l + 1];
		df[l] = dc[l] & Ct(l) & gD(f[l]);
		dz[l] = dc[l] & gD(z[l]);
	}
}
void GRU::backwardPropagation() {

	for (int l = layers - 2; l >= 0; --l) {
		//calculate the recurrent error 
		dc[l + 1] &= f[l + 1]; //backprop through forget gate
		dc[l + 1] += rz[l].T() * dz[l + 1] + rf[l].T() * df[l + 1]; //add recurrent error
		if (l != layers - 2) { //if this is not the output layer add feed forward error
			dc[l + 1] += wz[l + 1].T() * dz[l + 2] + wf[l + 1].T() * df[l + 2];
		}
		df[l + 1] = Ct_1(l + 1)& dc[l + 1] & gD(Ft(l + 1)); //calc forget gate delta
		dz[l + 1] = dc[l + 1] & gD(Zt(l + 1));  //calc input gate delta 
		//Get the gradients
		rz_GradientStorage[l] -= dz[l + 1] * Zt_1(l + 1) & lr;
		wz_GradientStorage[l] -= dz[l + 1] * Zt(l) & lr;
		bz_GradientStorage[l] -= dz[l + 1] & lr;

		rf_GradientStorage[l] -= df[l + 1] * Ft_1(l + 1) & lr;
		wf_GradientStorage[l] -= df[l + 1] * Ft(l) & lr;
		bf_GradientStorage[l] -= df[l + 1] & lr;
	}
}
void GRU::BPTT() {
	while (bpZ.size() > 0) {
		backwardPropagation();
		f = bpF.back(); 
		bpZ.pop_back();
		bpF.pop_back();
		bpC.pop_back();
	}
}
void GRU::initializeGradientStorage() {
	//sets the stored gradients to the weights
	//eventually we will set the weights to stored gradients once we sum the gradients from backprop
	for (int i = 0; i < layers - 1; ++i) {
		bz_GradientStorage[i] = bz[i];
		wz_GradientStorage[i] = wz[i];
		rz_GradientStorage[i] = rz[i];

		bf_GradientStorage[i] = bf[i];
		wf_GradientStorage[i] = wf[i];
		rf_GradientStorage[i] = rf[i];
	}
}
void GRU::SetWeightsToGradientSums() {
	for (int i = 0; i < layers - 1; ++i) {
		bz[i] = bz_GradientStorage[i];
		wz[i] = wz_GradientStorage[i];
		rz[i] = rz_GradientStorage[i];

		bf[i] = bf_GradientStorage[i];
		wf[i] = wf_GradientStorage[i];
		rf[i] = rf_GradientStorage[i];
	}
}
void GRU::updateWeights() {
	for (int l = 0; l < layers - 1; ++l) {
		wz_GradientStorage[l] -= dz[l + 1] * z[l] & lr;
		bz_GradientStorage[l] -= dz[l + 1] & lr;
		rz_GradientStorage[l] -= dz[l + 1] * Zt(l + 1);
		
		wf_GradientStorage[l] -= df[l + 1] * f[l] & lr;
		bf_GradientStorage[l] -= df[l + 1] & lr;
		rf_GradientStorage[l] -= df[l + 1] * Ft(l + 1);
	}
}
void GRU::clearActivations() {
	//Erases all activations. This method may need to be deleted for certain types of learning problems. 
	//Namely, sequences that are dependent upon prior sequences.

	bpZ.clear();
	bpF.clear();
	bpC.clear();

	for (int i = 0; i < z.size(); ++i) {
		for (int j = 0; j < z[i].size(); ++j) {
			z[i][j] = 0;
			f[i][j] = 0;
			c[i][j] = 0;
		}
	}
}
Vector & GRU::g(Vector & z)
{
	//sigmoid function is used opposed to tanH as the derivative is more easily used as we do not need to store the inputs, (only the activations)
	//sigmoid function  1 / 1 + e^-x
	for (int i = 0; i < z.size(); ++i) {
		z[i] = 1 / (1 + pow(E, -z[i]));
	}
	return z;
}
Vector GRU::gD(Vector z)
{
	//derivative of sigmoid function (post crush). Source: Andrew Ng (coursera) Machines Learning Standford
	for (int i = 0; i < z.size(); ++i) {
		z[i] *= (1 - z[i]);
	}
	return z;
}
Vector & GRU::h(Vector & z)
{
	//sigmoid function is used opposed to tanH as the derivative is more easily used as we do not need to store the inputs, (only the activations)
	//sigmoid function  1 / 1 + e^-x
	for (int i = 0; i < z.size(); ++i) {
		z[i] = (pow(E, z[i]) - pow(E, -z[i])) / (pow(E, z[i]) + pow(E, -z[i]));
	}
	return z;
}
Vector GRU::hD(Vector z)
{
	//derivative of sigmoid function (post crush). Source: Andrew Ng (coursera) Machines Learning Standford
	for (int i = 0; i < z.size(); ++i) {
		z[i] = 1 - (2 / (pow(E, 2 * z[i]) + 1));
	}
	return z;
}