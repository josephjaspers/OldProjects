#pragma once
#ifndef GateNetwork_h
#define GateNetwork_h
#include "Matrices.h"
#include <vector>
#include <cstdlib>
using namespace std;
using namespace Matrices;
class GateNetwork {

	const double e = 2.7182818;
	//const double e = 2.71828182845904523536028747135266249775724709369995;

	//write gate
	vector<vector<Vector>> bpZ;			//Backpropagation activations of Z activations 
	vector<Vector> z;					//Current activations 
	Vector* dz;							//delta (error)
	Vector* bz;							//bias
	Matrix* rz;							//reccurent weights
	Matrix* wz;							//normal weights

	Matrix* wz_GradientStorage;			//stores gradients at BPPT than copies them back to originals 
	Matrix* rz_GradientStorage;
	Vector* bz_GradientStorage;

	//input
	vector<vector<Vector>> bpI;			//Backpropagation activations of Z activations 
	vector<Vector> i;					//Current activations 
	Vector* di;							//delta (error)
	Vector* bi;							//bias
	Matrix* ri;							//reccurent weights
	Matrix* wi;							//normal weights

	Matrix* wi_GradientStorage;			//stores gradients at BPPT than copies them back to originals 
	Matrix* ri_GradientStorage;
	Vector* bi_GradientStorage;

	//forget gate
	vector<vector<Vector>> bpF;			//Backpropagation activations of F activations
	vector<Vector> f;					//current activations
	Vector* df;							//delta (Error)
	Vector* bf;							//bias
	Matrix* rf;							//recurrent weights
	Matrix* wf;							//normal weights

	Matrix* wf_GradientStorage;			//stores gradients at BPPT than copies them back to originals 
	Matrix* rf_GradientStorage;
	Vector* bf_GradientStorage;

	//output gate
	vector<vector<Vector>> bpO;			//Backpropagation activations of O activations 
	vector<Vector> o;					//Current activations 
	Vector* od;							//delta (error)
	Vector* bo;							//bias
	Matrix* ro;							//reccurent weights
	Matrix* wo;							//normal weights

	Matrix* wo_GradientStorage;			//stores gradients at BPPT than copies them back to originals 
	Matrix* ro_GradientStorage;
	Vector* bo_GradientStorage;

	vector<Vector> c;					//cell state
	Vector* dc;							//cell state error 
	vector<vector<Vector>> bpC;			//cell state activations for BPTT

	vector<Vector> y;					//output
	Vector* dy;							//output error 
	vector<vector<Vector>> bpY;			//output activations for BPTT


	int layers;							//number of layers
	vector<int> networkStruct;			//showcases numbers of nodes in specific layers


	double lr = .03; //learning rate

	vector<vector<Vector>> inputSet;	//input set
	vector<Vector> outputSet;			//output set

public:
	//Constructor
	GateNetwork(vector<int> structure); //constructor -- initializes matrices and network sizes
	~GateNetwork();						//decon
										//Training Aspects 
	void addTrainingData(const vector<double>& inputSet, const vector<double>& outpuSet);
	void addTrainingData(const vector<vector<double>>& inputSet, const vector<double>& outputset);
	void train();												//train over the data set 1 time
	void train(int i);											//train over data set i times
	void train(vector<double>& input, vector<double> & output); //train given input/output st 
	void train(vector<vector<double>>& input, vector<double> & output); //train given input set (multiple time stamps) and outputset

																		//set leraning rate 
	void setLearningRate(double rate) {
		lr = rate;
	}					//set learning rate - need to add more apropriate accessors/getters

						//predict
	vector<double> predict(const vector<double>& inputdata);			//predict methods for running the NN
	vector<double> predict(const vector<vector<double>>& inputData);	//predict methods -- will add overloaded options
																		//save/read
	void read(ifstream & is);									//read/write functions (not yet implemented)
	void write(ofstream& os);

private:
	Vector& forwardPropagation(Vector& input);					//Forward Propagation
	void backwardPropagation(Vector& output);					//"Feed forward" BP (for the first call of Back prop)
	void backwardPropagation();									//Bp for BPTT (also updates weight simaultaneously)
	void BPTT(Vector & output);									//iteratively calls backprop for all time steps (will add truncation option later)
	void updateWeights();										//updates the weights for Feed forward BP
	void updateWeights_storage();
	void resetGradientStorage();
	void addGradients();

	void updateWeightsBp1();

	void clearActivations();									//clears the activations of each gate of the GateNetwork
	void clearDelta();

	Vector& pseudoSoft_Max(Vector & v);

	Vector& g(Vector& z);										//sigmoid function
	Vector sig(Vector z);
	Vector gD(Vector z);										//sigmoid derivative
	Vector &h(Vector & z);										//tanh function
	Vector tanh(Vector z);
	Vector hD(Vector z);										//tanh derivative 

	Vector& Ct(int l) { return bpC.back()[l]; }					//cellstate at current time step
	Vector& Ct_1(int l) { return bpC[bpC.size() - 1][l]; }		//cellstate at current timestep - 1

	Vector& Zt(int l) { return bpZ.back()[l]; }					//input activation at current time step
	Vector& Zt_1(int l) { return bpZ[bpZ.size() - 1][l]; }		//input activation at current time step - 1

	Vector& It(int l) { return bpZ.back()[l]; }					//input activation at current time step
	Vector& It_1(int l) { return bpZ[bpZ.size() - 1][l]; }		//input activation at current time step - 1


	Vector& Ft(int l) { return bpF.back()[l]; }					//forget activation at current time step
	Vector& Ft_1(int l) { return bpF[bpF.size() - 1][l]; }		//forget activation at current time step - 1

	Vector& Ot(int l) { return bpO.back()[l]; }					//output activation at current time step
	Vector& Ot_1(int l) { return bpO[bpF.size() - 1][l]; }		//output activation at current time step - 1

	Vector& Yt(int l) { return bpY.back()[l]; }					//y activation at current time step
	Vector& Yt_1(int l) { return bpY[bpY.size() - 1][l]; }		//y activation at current time step - 1
};
#endif