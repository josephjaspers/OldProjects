#pragma once
#ifndef GRU_h
#define GRU_h
#include "Matrices.h"
#include <vector>
#include <cstdlib>
using namespace std;
using namespace Matrices;
class GRU {
	const double E = 2.7182818281828;

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

	vector<Vector> c;					//cell state
	Vector* dc;							//cell state error 
	vector<vector<Vector>> bpC;			//cell state activations for BPTT

	int layers;							//number of layers
	vector<int> networkStruct;			//showcases numbers of nodes in specific layers

	double lr = .03;					//learning rate

	vector<vector<Vector>> inputSet;	//input set
	vector<Vector> outputSet;			//output set

public:
	//Constructor
	GRU(vector<int> structure); //constructor -- initializes matrices and network sizes
	~GRU();						//decon
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
	double getLearningRate() {
		return lr;
	}
	//predict
	vector<double> predict(const vector<double>& inputdata);			//predict methods for running the NN
	vector<double> predict(const vector<vector<double>>& inputData);	//predict methods -- will add overloaded options
	void pseudoSoft_Max(Vector & v);
	//save/read
	void read(ifstream & is);									//read/write functions (not yet implemented)
	void write(ofstream& os);

private:
	Vector& forwardPropagation(Vector& input);					//Forward Propagation
	void backwardPropagation(Vector& output);					//"Feed forward" BP (for the first call of Back prop)
	void backwardPropagation();									//Bp for BPTT (also updates weight simaultaneously)
	void BPTT();												//iteratively calls backprop for all time steps (will add truncation option later)
	void updateWeights();										//updates the weights for Feed forward BP
	void initializeGradientStorage();
	void SetWeightsToGradientSums();

	void clearActivations();									//clears the activations of each gate of the GRU

	Vector& g(Vector& z);										//sigmoid function
	Vector gD(Vector z);										//sigmoid derivative
	Vector & h(Vector & z);										//tanh function
	Vector hD(Vector z);										//tanh derivative 

	Vector& Ct(int l) { return bpC.back()[l]; }					//cellstate at current time step
	Vector& Ct_1(int l) { return bpC[bpC.size() - 1][l]; }		//cellstate at current timestep - 1

	Vector& Zt(int l) { return bpZ.back()[l]; }					//input activation at current time step
	Vector& Zt_1(int l) { return bpZ[bpZ.size() - 1][l]; }		//input activation at current time step - 1

	Vector& Ft(int l) { return bpF.back()[l]; }					//forget activation at current time step
	Vector& Ft_1(int l) { return bpF[bpF.size() - 1][l]; }		//forget activation at current time step - 1
};

#endif