// gradientDescent.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "gradientDescent.h"
#include <iostream>
gradientDescent::gradientDescent(int features)
{
	constants = vector<double>(features + 1);
	gradientDescent::features = features;
}

void gradientDescent::train()
{
	updateWeights();
}

void gradientDescent::train(int i)
{
	while (i > 0) {
		updateWeights();
		--i;
	}
}

void gradientDescent::addTrainingData(vector<double> data, double output)
{
	if (data.size() != features) {
		throw exception("invalid number of features");
	}
	trainingSet.push_back(data);
	outputSet.push_back(output);
}

double gradientDescent::evaluate(vector<double> data)
{
	if (data.size() != features) {//Excludes y intercept
		throw exception("invalid number of features");
	}

	double total = 0;
	for (int i = 0; i < data.size(); ++i) {
		total += data[i] * constants[i];
	}
	total += constants[features - 1]; //adds the y intercept 
	return total;
}

vector<double> gradientDescent::getConstants()
{
	return constants;
}

void gradientDescent::updateWeights()
{
	for (int i = 0; i < trainingSet.size(); ++i) {
		for (int j = 0; j < features; ++j) {
			costFunction(j, i);
		}
	}
}
double gradientDescent::HypothesisTheta(int index)
{
	double total = 0;
	for (int i = 0; i < features + 1; ++i) {
		if (i == features) {
			total += constants[i]; //Y intercept
		}
		else {
			total += trainingSet[index][i] * constants[i];
		}
	}
	return total;
}
double gradientDescent::regularization(int j)
{
	if (!regularizationOn || j == features - 1) {
		return 1; //For not updating the Y intercept
	}
	double m = trainingSet.size();

	double lambda = regularizationConst;
	return 1 - learningRate * (lambda / m);
}
void gradientDescent::costFunction(int j, int i)
{
	int m = trainingSet.size();
	constants[j] += (y(i) - HypothesisTheta(i)) * x(i, j) * lr() * r(j);
}

double gradientDescent::x(int i, int j)
{
	return trainingSet[i][j];
}

double gradientDescent::y(int i)
{
	return outputSet[i];
}

int main() {
	gradientDescent gd = gradientDescent(3);

	double c1 = rand()%3 + 10;
	double c2 = rand()%3 + 10;
	double c3 = rand()%3 + 10;

	double f1;
	double f2;
	double f3;
	double ans;

	for (int i = 0; i < 1000; i++) {
		f1 = rand() % 5 + 10;
		f2 = rand() % 5 + 10;
		f3 = rand() % 5 + 10;
		ans = f1 * c1 + f2 * c2 + f3 * c3;
		gd.addTrainingData(vector<double> {f1, f2, f3}, ans);
	}
	int train = 1;
	while (train > 0) {
		cout << "train ? " << endl;
		cin >> train;
		gd.train(train);

		f1 = rand() % 3 + 10;
		f2 = rand() % 3 + 10;
		f3 = rand() % 3 + 10;


		//reTrain the data looks over the given dataSet and reiterates gradient Descent upon it 

		cout << "This test involves three variables, with respective constants - " << c1 << " " << c2 <<
			" " << c3 << endl;

		cout << " THE TOTAL SHOULD BE " << (f1 * c1 + f2 * c2 + f3 * c3) << endl;
		cout << "Testing parameters " << f1 << " " << f2 << " " << f3 << " " << "\nevaluates to: "
			<< gd.evaluate(vector<double> {f1, f2, f3}) << endl;
		cout << "The constants were evaluated to be " << endl;
		auto c = gd.getConstants();
		for (int i = 0; i < c.size(); ++i) {
			cout << c[i] << endl;
		}

	}
	int wait;
	cin >> wait;
}

