#include "stdafx.h"
#include "ANN.h"

#include <iostream>
void XORTest() {
	cout << "Neural Network XOR test " << endl;
	cout << "Inputs 2" << endl << "hidden Layers 2 " << endl << "hidden nodes 10" << endl << "outpus 1" << endl;
	cout << "input seed for rand (input intenger)" << endl;
	int seed;
	cin >> seed;
	srand(seed);
	ANN ann(2, 1, 200, 1);
	ann.addTrainingData(vector<double> {0, 0}, vector<double> {1});
	ann.addTrainingData(vector<double> {1, 0}, vector<double> {0});
	ann.addTrainingData(vector<double> {0, 1}, vector<double> {0});
	ann.addTrainingData(vector<double> {1, 1}, vector<double> {1});
	int retrain = 1;

	while (retrain > 0) {

		std::cout << "train how many times" << endl;
		std::cin >> retrain;

		ann.train(retrain);

		std::vector<double> prediction = ann.predict(std::vector<double>{ 1, 1 });
		std::cout << " testing  1 , 1 " << endl;
		for (int i = 0; i < prediction.size(); ++i) {
			std::cout << std::fixed << prediction[i] << " " << std::endl;
		}
		prediction = ann.predict(std::vector<double>{ 0, 0 });
		std::cout << " testing  0 , 0 " << endl;
		for (int i = 0; i < prediction.size(); ++i) {
			std::cout << std::fixed << prediction[i] << " " << std::endl;
		}
		prediction = ann.predict(std::vector<double>{ 0, 1 });
		std::cout << " testing  0 , 1 " << endl;
		for (int i = 0; i < prediction.size(); ++i) {
			std::cout << std::fixed << prediction[i] << " " << std::endl;
		}
		prediction = ann.predict(std::vector<double>{ 1, 0 });
		std::cout << " testing  1 , 0  " << endl;
		for (int i = 0; i < prediction.size(); ++i) {
			std::cout << std::fixed << prediction[i] << " " << std::endl;
		}
		//ann.printNetwork();
	}
}
int main() {
	XORTest();
}