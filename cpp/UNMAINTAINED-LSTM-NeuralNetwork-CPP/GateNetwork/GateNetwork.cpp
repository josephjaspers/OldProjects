// GateNetwork.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "GateNetwork.h"

/*
The purpose of this RNN is to generate clear code. I have attempted generate code that is as closely to as possible as the original
algorithms for the purpose of clarity.

Commented out are mathematical code variants. All code variants utilize overloaded operators in the given Matrix library and may be used interchangeably as is.


Current implemetation uses z variant of BPTT and updates the weights at each timestamp.
This is done for the sake of clarity.

To implement standard BPTT simply create z copy of the weights to calculate the gradients with BPTT and backpropagation and then call update weights as normal.
*/
GateNetwork::GateNetwork(vector<int> structure)
{
	layers = structure.size();
	networkStruct = structure;

	c = vector<Vector>(layers);
	dc = new Vector[layers];
	y = vector<Vector>(layers);
	dy = new Vector[layers];

	z = vector<Vector>(layers);
	dz = new Vector[layers];
	bz = new Vector[layers - 1];
	wz = new Matrix[layers - 1];
	rz = new Matrix[layers - 1];
	bz_GradientStorage = new Vector[layers - 1];
	wz_GradientStorage = new Matrix[layers - 1];
	rz_GradientStorage = new Matrix[layers - 1];

	GateNetwork::i = vector<Vector>(layers);
	di = new Vector[layers];
	bi = new Vector[layers - 1];
	wi = new Matrix[layers - 1];
	ri = new Matrix[layers - 1];
	bi_GradientStorage = new Vector[layers - 1];
	wi_GradientStorage = new Matrix[layers - 1];
	ri_GradientStorage = new Matrix[layers - 1];

	f = vector<Vector>(layers);
	rf = new Matrix[layers - 1];
	wf = new Matrix[layers - 1];
	bf = new Vector[layers - 1];
	df = new Vector[layers];
	bf_GradientStorage = new Vector[layers - 1];
	wf_GradientStorage = new Matrix[layers - 1];
	rf_GradientStorage = new Matrix[layers - 1];

	o = vector<Vector>(layers);
	ro = new Matrix[layers - 1];
	wo = new Matrix[layers - 1];
	bo = new Vector[layers - 1];
	od = new Vector[layers];
	bo_GradientStorage = new Vector[layers - 1];
	wo_GradientStorage = new Matrix[layers - 1];
	ro_GradientStorage = new Matrix[layers - 1];

	for (int i = 0; i < structure.size() - 1; ++i) {
		y[i] = Vector(structure[i]);
		dc[i] = Vector(structure[i]);
		c[i] = Vector(structure[i]);
		dc[i] = Vector(structure[i]);

		z[i] = Vector(structure[i]);
		dz[i] = Vector(structure[i]);
		bz[i] = Vector(structure[i + 1]);
		wz[i] = Matrix(structure[i + 1], structure[i]);
		rz[i] = Matrix(structure[i + 1], structure[i + 1]);
		//initialize in positive range (network trains the input gate first, write gate writes everything))
		randomize(bz[i], 0, 4);
		randomize(wz[i], 0, 4);
		randomize(rz[i], 0, 4);
		bz_GradientStorage[i] = Vector(structure[i + 1]);
		wz_GradientStorage[i] = Matrix(structure[i + 1], structure[i]);
		rz_GradientStorage[i] = Matrix(structure[i + 1], structure[i + 1]);

		GateNetwork::i[i] = Vector(structure[i]);
		di[i] = Vector(structure[i]);
		bi[i] = Vector(structure[i + 1]);
		wi[i] = Matrix(structure[i + 1], structure[i]);
		ri[i] = Matrix(structure[i + 1], structure[i + 1]);
		randomize(bi[i], -4, 4);
		randomize(wi[i], -4, 4);
		randomize(ri[i], -4, 4);
		bi_GradientStorage[i] = Vector(structure[i + 1]);
		wi_GradientStorage[i] = Matrix(structure[i + 1], structure[i]);
		ri_GradientStorage[i] = Matrix(structure[i + 1], structure[i + 1]);

		f[i] = Vector(structure[i]);
		df[i] = Vector(structure[i]);
		bf[i] = Vector(structure[i + 1]);
		wf[i] = Matrix(structure[i + 1], structure[i]);
		rf[i] = Matrix(structure[i + 1], structure[i + 1]);
		//initialize forget weights to negative values (network learns to remember)
		randomize(bf[i], -4, 0);
		randomize(wf[i], -4, 0);
		randomize(rf[i], -4, 0);
		bf_GradientStorage[i] = Vector(structure[i + 1]);
		wf_GradientStorage[i] = Matrix(structure[i + 1], structure[i]);
		rf_GradientStorage[i] = Matrix(structure[i + 1], structure[i + 1]);

		o[i] = Vector(structure[i]);
		od[i] = Vector(structure[i]);
		bo[i] = Vector(structure[i + 1]);
		wo[i] = Matrix(structure[i + 1], structure[i]);
		ro[i] = Matrix(structure[i + 1], structure[i + 1]);
		randomize(bo[i], -4, 4);
		randomize(wo[i], -4, 4);
		randomize(ro[i], -4, 4);
		bo_GradientStorage[i] = Vector(structure[i + 1]);
		wo_GradientStorage[i] = Matrix(structure[i + 1], structure[i]);
		ro_GradientStorage[i] = Matrix(structure[i + 1], structure[i + 1]);
	}
	y[layers - 1] = Vector(structure.back());
	dc[layers - 1] = Vector(structure.back());

	c[layers - 1] = Vector(structure.back());
	dc[layers - 1] = Vector(structure.back());

	z[layers - 1] = Vector(structure.back());
	dz[layers - 1] = Vector(structure.back());	

	i[layers - 1] = Vector(structure.back());
	di[layers - 1] = Vector(structure.back());

	f[layers - 1] = Vector(structure.back());
	df[layers - 1] = Vector(structure.back());

	o[layers - 1] = Vector(structure.back());
	od[layers - 1] = Vector(structure.back());
}

GateNetwork::~GateNetwork()
{
	delete[] dc;
	delete[] dy;

	delete[] dz;
	delete[] bz;
	delete[] wz;
	delete[] rz;
	delete[] bz_GradientStorage;
	delete[] wz_GradientStorage;
	delete[] rz_GradientStorage;

	delete[] di;
	delete[] bi;
	delete[] wi;
	delete[] ri;
	delete[] bi_GradientStorage;
	delete[] wi_GradientStorage;
	delete[] ri_GradientStorage;

	delete[] df;
	delete[] bf;
	delete[] wf;
	delete[] rf;
	delete[] bf_GradientStorage;
	delete[] wf_GradientStorage;
	delete[] rf_GradientStorage;

	delete[] od;
	delete[] bo;
	delete[] wo;
	delete[] ro;
	delete[] bo_GradientStorage;
	delete[] wo_GradientStorage;
	delete[] ro_GradientStorage;
}

void GateNetwork::addTrainingData(const vector<double>& i, const vector<double>& o)
{
	inputSet.push_back(vector<Vector> { Vector(i) });
	outputSet.push_back(Vector(o));
}
void GateNetwork::addTrainingData(const vector<vector<double>>& inputData, const vector<double>& o)
{
	vector<Vector> iData(inputData.size());
	for (int i = 0; i < inputData.size(); ++i) {
		iData[i] = Vector(inputData[i]);
	}
	inputSet.push_back(iData);
	outputSet.push_back(Vector(o));
}

void GateNetwork::train()
{
	for (int d = 0; d < inputSet.size(); ++d) {
		resetGradientStorage();
		for (int j = 0; j < inputSet[d].size(); ++j) {
			bpZ.push_back(z);
			bpI.push_back(i);
			bpF.push_back(f);
			bpC.push_back(c);
			bpO.push_back(o);
			bpY.push_back(y);
			forwardPropagation(inputSet[d][j]);
		}
		BPTT(outputSet[d]); //BPTT will calculate the recurrent error
		addGradients();
	}
}
void GateNetwork::train(int i)
{
	//Enables training over z batch of the data set multiple times.
	while (i > 0) {
		train();
		--i;
	}
}
vector<double> GateNetwork::predict(const vector<double>& inputdata)
{
	return forwardPropagation(Vector(inputdata)).getCpyVect();
}
vector<double> GateNetwork::predict(const vector<vector<double>>& inputdata)
{
	for (int i = 0; i < inputdata.size() - 1; ++i) {
		forwardPropagation(Vector(inputdata[i]));
	}
	return forwardPropagation(Vector(inputdata.back())).getCpyVect();
}
void GateNetwork::clearDelta() {
	for (int i = 0; i < layers; ++i) {
		for (int j = 0; j < dy[i].size(); ++j) {
			dy[i][j] = 0;
			dc[i][j] = 0;
			od[i][j] = 0;
			df[i][j] = 0;
			dz[i][j] = 0;
		}
	}
}
Vector& GateNetwork::pseudoSoft_Max(Vector& v) {
	double sum = 0;
	//get sum
	for (int i = 0; i < v.length(); ++i) {
		v[i] = pow(v[i], e);
		sum += v[i];
	}
	double softMaxSum = 0;
	for (int i = 0; i < v.length(); ++i) {
		//normal distribution
		v[i] = v[i] / sum;
		//exponentiate 
		v[i] = pow(abs(v[i]), e);
		softMaxSum += v[i];
	}
	for (int i = 0; i < v.length(); ++i) {
		v[i] /= softMaxSum;
	}
	return v;
}
Vector& GateNetwork::forwardPropagation(Vector & input)
{
	y[0] = input;
	for (int l = 1; l < layers; ++l) {
		z[l] = rz[l - 1] * y[l] + wz[l - 1] * y[l - 1] + bz[l - 1];
		i[l] = ri[l - 1] * y[l] + wi[l - 1] * y[l - 1] + bi[l - 1];
		f[l] = rf[l - 1] * y[l] + wf[l - 1] * y[l - 1] + bf[l - 1];
		o[l] = ro[l - 1] * y[l] + wo[l - 1] * y[l - 1] + bo[l - 1];

		g(i[l]);
		h(z[l]);
		g(f[l]);
		g(o[l]);
		c[l] &= f[l];
		c[l] += (z[l] & i[l]);

		y[l] = sig(c[l]) & o[l];
	}
	return pseudoSoft_Max(y[layers - 1]);
	//return y[layers - 1];

}
void GateNetwork::backwardPropagation(Vector & output)
{
	dy[layers - 1] = y[layers - 1] - output;
	dc[layers - 1] = dy[layers - 1] & o[layers - 1];
	od[layers - 1] = dy[layers - 1] & sig(c[layers - 1]);
	df[layers - 1] = dc[layers - 1] & Ct(layers - 1);
	dz[layers - 1] = dc[layers - 1] & i[layers - 1];
	di[layers - 1] = dc[layers - 1] & z[layers - 1];
	for (int l = layers - 2; l > 0; --l) {
		dy[l] = wz[l].T() * dz[l + 1] + wf[l].T() * df[l + 1] + wi[l].T() * di[l + 1] + wo[l].T() * od[l + 1];
		dc[l] = dy[l] & o[l] & gD(sig(c[l]));
		od[l] = dy[l] & sig(c[l]) & gD(o[l]);
		df[l] = dc[l] & Ct(l) & gD(f[l]);
		dz[l] = (dc[l] & hD(z[l]) & i[l]);
		di[l] = (dc[l] & gD(i[l]) & z[l]);
	}
}
void GateNetwork::backwardPropagation() {

	for (int l = layers - 2; l > -1; --l) {
		//calculate the recurrent error 
		dy[l + 1] = rz[l].T() * dz[l + 1] + ri[l].T() * di[l + 1] + rf[l].T() * df[l + 1] + ro[l].T() * od[l + 1];
		if (l != layers - 2) {
			dy[l + 1] += wz[l + 1].T() * dz[l + 2] + wi[l + 1].T() * di[l + 2] + wf[l + 1].T() * df[l + 2] + wo[l + 1].T() * od[l + 2];
		}
		dc[l + 1] &= f[l + 1]; //backprop through forget gate
		dc[l + 1] += dy[l + 1] & Ot(l + 1) & gD(sig(Ct(l + 1)));
		od[l + 1] = dc[l + 1] & sig(Ct(l + 1)) & gD(Ot(l + 1));
		df[l + 1] = Ct_1(l + 1)& dc[l + 1] & gD(Ft(l + 1)); //calc forget gate delta
		dz[l + 1] = (dc[l + 1] & hD(Zt(l + 1)) & It(l + 1));  //calc input gate delta 
		di[l + 1] = (dc[l + 1] & gD(It(l + 1)) & Zt(l + 1));
	}
}
void GateNetwork::BPTT(Vector& output) {
	backwardPropagation(output); 
	updateWeights();
	while (bpZ.size() > 0) {
		backwardPropagation();
		updateWeights_storage();
		f = bpF.back();
		
		bpZ.pop_back();
		bpI.pop_back();
		bpF.pop_back();
		bpC.pop_back();
		bpO.pop_back();
		bpY.pop_back();
	}
}
void GateNetwork::resetGradientStorage() {
	for (int l = 0; l < layers - 1; ++l) {
		Vector::fill(bz_GradientStorage[l], 0);
		Matrix::fill(wz_GradientStorage[l], 0);
		Matrix::fill(rz_GradientStorage[l], 0);
	
		Vector::fill(bi_GradientStorage[l], 0);
		Matrix::fill(wi_GradientStorage[l], 0);
		Matrix::fill(ri_GradientStorage[l], 0);

		Vector::fill(bf_GradientStorage[l], 0);
		Matrix::fill(wf_GradientStorage[l], 0);
		Matrix::fill(rf_GradientStorage[l], 0);

		Vector::fill(bo_GradientStorage[l], 0);
		Matrix::fill(wo_GradientStorage[l], 0);
		Matrix::fill(ro_GradientStorage[l], 0);
	}
}
void GateNetwork::addGradients() {
	for (int l = 0; l < layers - 1; ++l) {
		bz[l] += bz_GradientStorage[l] & lr;
		wz[l] += wz_GradientStorage[l] & lr;
		rz[l] += rz_GradientStorage[l] & lr;

		bi[l] += bi_GradientStorage[l] & lr;
		wi[l] += wi_GradientStorage[l] & lr;
		ri[l] += ri_GradientStorage[l] & lr;

		bf[l] += bf_GradientStorage[l] & lr;
		wf[l] += wf_GradientStorage[l] & lr;
		rf[l] += rf_GradientStorage[l] & lr;

		bo[l] += bo_GradientStorage[l] & lr;
		wo[l] += wo_GradientStorage[l] & lr;
		ro[l] += ro_GradientStorage[l] & lr;
	}
}
void GateNetwork::updateWeights() {
	//should only be called after 1st ff BP.
	for (int l = 0; l < layers - 1; ++l) {
		wz_GradientStorage[l] -= dz[l + 1] * z[l];
		bz_GradientStorage[l] -= dz[l + 1];
		rz_GradientStorage[l] -= dz[l + 1] * Zt(l + 1);

		wi_GradientStorage[l] -= di[l + 1] * i[l];
		bi_GradientStorage[l] -= di[l + 1];
		ri_GradientStorage[l] -= di[l + 1] * It(l + 1);

		wf_GradientStorage[l] -= df[l + 1] * f[l];
		bf_GradientStorage[l] -= df[l + 1];
		rf_GradientStorage[l] -= df[l + 1] * Ft(l + 1);

		wo_GradientStorage[l] -= od[l + 1] * o[l];
		bo_GradientStorage[l] -= od[l + 1];
		ro_GradientStorage[l] -= od[l + 1] * Ot(l + 1);
	}
}
void GateNetwork::updateWeights_storage() {
	//should only be called after 1st ff BP.
	for (int l = 0; l < layers - 1; ++l) {
		wz_GradientStorage[l] -= dz[l + 1] * Zt(l);
		bz_GradientStorage[l] -= dz[l + 1];
		rz_GradientStorage[l] -= dz[l + 1] * Zt_1(l + 1);

		wi_GradientStorage[l] -= di[l + 1] * It(l);
		bi_GradientStorage[l] -= di[l + 1];
		ri_GradientStorage[l] -= di[l + 1] * It_1(l + 1);

		wf_GradientStorage[l] -= df[l + 1] * Ft(l);
		bf_GradientStorage[l] -= df[l + 1];
		rf_GradientStorage[l] -= df[l + 1] * Ft_1(l + 1);

		wo_GradientStorage[l] -= od[l + 1] * Ot(l);
		bo_GradientStorage[l] -= od[l + 1];
		ro_GradientStorage[l] -= od[l + 1] * Ot_1(l + 1);
	}
}
void GateNetwork::clearActivations() {
	//Erases all activations. This method may need to be deleted for certain types of learning problems. 
	//Namely, sequences that are dependent upon prior sequences.

	bpZ.clear();
	bpF.clear();
	bpC.clear();
	bpO.clear();

	for (int i = 0; i < z.size(); ++i) {
		for (int j = 0; j < z[i].size(); ++j) {
			z[i][j] = 0;
			f[i][j] = 0;
			c[i][j] = 0;
			o[i][j] = 0;
		}
	}
}
Vector GateNetwork::sig(Vector z) {
	for (int i = 0; i < z.size(); ++i) {
		z[i] = 1 / (1 + pow(e, -z[i]));
	}
	return z;
}
Vector & GateNetwork::g(Vector & z)
{
	//sigmoid function is used opposed to tanH as the derivative is more easily used as we do not need to store the inputs, (only the activations)
	//sigmoid function  1 / 1 + e^-x
	for (int i = 0; i < z.size(); ++i) {
		z[i] = 1 / (1 + pow(e, -z[i]));
	}
	return z;
}
Vector GateNetwork::gD(Vector z)
{
	//derivative of sigmoid function (post crush). Source: Andrew Ng (coursera) Machines Learning Standford
	for (int i = 0; i < z.size(); ++i) {
		z[i] *= (1 - z[i]);
	}
	return z;
}
Vector& GateNetwork::h(Vector & z) {
	for (int i = 0; i < z.length(); ++i) {
		z[i] = (pow(e, z[i]) - pow(e, -z[i])) / (pow(e, z[i]) + pow(e, -z[i]));
		//z[i] = std::tanh(z[i]);
	}
	return z;
}
Vector GateNetwork::tanh(Vector z) {
	for (int i = 0; i < z.length(); ++i) {
		//z[i] = (pow(e, z[i]) - pow(e, -z[i])) / (pow(e, z[i]) + pow(e, -z[i]));
		//z[i] = std::tanh(z[i]); //tanh
		z[i] = (pow(e, z[i]) - pow(e, -z[i])) / (pow(e, z[i]) + pow(e, -z[i]));
	
	//tanh = (e^x - e^-x)/(e^x + e^-x)
	}
	return z;
}
Vector GateNetwork::hD(Vector z)
{
	//derivative of sigmoid function (post crush). Source: Andrew Ng (coursera) Machines Learning Standford
	for (int i = 0; i < z.size(); ++i) {
		//z[i] = 1 - (2 / (pow(e, 2 * z[i]) + 1));
		z[i] = (1 - pow(z[i], 2)); //tanh
		//(1 - tanh(x)^2)
	}
	return z;
}