#include "stdafx.h"
#include <cstdlib>
#include "jANN.h"
#include "Matrix.h"
#include <fstream>
#include <ostream>
#include <iostream>
#include <cstdlib>
#include <string>
#include <list>
#include <string>
#include <sstream>
using namespace std;
void printEval(vector<double> ev) {
	double max = -1;
	int maxpos = -1;
	for (int i = 0; i < ev.size(); ++i) {
		if (ev[i] > max) {
			max = ev[i];
			maxpos = i;
		}
		cout << ev[i] << " ";
	}
	cout << " (" << maxpos << ")" << endl;
}
int getCorrect(vector<double>& output) {
	int pos = -1;
	double hyp = -1;
	for (int i = 0; i < output.size(); ++i) {
		if (hyp < output[i]) {
			hyp = output[i];
			pos = i;
		}
	}
	return pos;
}

vector<double>& featureScaling(vector<double>& table, double min, double max) {
	for (int i = 0; i < table.size(); ++i) {
		table[i] = (table[i] - min) / (max - min);
	}
	return table;
}
vector<double> createOutputVector(int index, int outputs) {
	vector<double> o(outputs);
	o[index] = 1;
	return o;
}
vector<double> createInputVector(string v) {
	vector<double> data;
	stringstream ss(v);

	string store;
	//removes first input 
	getline(ss, store, ',');
	while (ss.good()) {
		getline(ss, store, ',');
		data.push_back(stod(store));
	}
	return data;
}
vector<double> createInputVectorSubmission(string v) {
	vector<double> data;
	stringstream ss(v);

	string store;
	while (ss.good()) {
		getline(ss, store, ',');
		data.push_back(stod(store));
	}
	return data;
}
static void getError(string fileName) {
	ifstream iFile(fileName);
	jANN ann;
	ann.read(iFile);
	iFile.close();

	ifstream is("\\Users\\joeyj\\Downloads\\train.csv");
	cout << "moving past first row" << endl;
	string tmp;
	getline(is, tmp, '\n');
	int i = 0;
	int correct = 0;
	while (getline(is, tmp, '\n')) {
		++i;
		int output = getCorrect(ann.predict(featureScaling(createInputVector(tmp), 0, 255)));
		if (output == getCorrect(createOutputVector(stoi(tmp), 10))) {
			++correct;
		}
	}
	is.close();
	cout << "Total correct: " << correct << endl;
	cout << "Total reviewed: " << i << endl;
	double percent = correct / i;
	cout << "Percent (correct / reviewed): " << percent << endl;

	int wait;
	cin >> wait;
}

static void csvTrain(string filename) {
	//Open training
	std::cout << "reading from \\Users\\joeyj\\Downloads\\train.csv" << endl;
	//generate neural network
	jANN ann(vector<int> {784, 25, 10});
	//ifstream is("meow7");
	//ann.read(is);
	int iterations = 0;
	string tmp;
	ifstream is = ifstream("\\Users\\joeyj\\Downloads\\train.csv");
	while (iterations != 100) {
		std::cout << "iteration: " << iterations << endl;
		if (is.is_open()) {
			std::cout << "ifstream open to train.csv" << endl;
		}
		else {
			std::cout << "opening file failed " << endl;
		}
		std::cout << "moving past first row" << endl;
		getline(is, tmp, '\n');
		int i = 0;
		while (getline(is, tmp, '\n')) {
			ann.train(featureScaling(createInputVector(tmp), 0, 255), createOutputVector(stoi(tmp), 10));
			++i;
			//cout << i << endl;
		}
		stringstream ss;
		ss << filename << iterations;
		ofstream os(ss.str());
		cout << " saving - " << ss.str() << endl;
		ann.write(os);
		os.close();

		++iterations;
		is.close();
	//	getError(ss.str());
	}
	++iterations;
	std::cout << iterations << endl;
	std::cout << "saving " << endl;
	filename = filename.append("Fin");
	ofstream os(filename);
	ann.write(os);
	os.close();
}

void csvT() {
	//Open training
	cout << "reading from \\Users\\joeyj\\Downloads\\train.csv" << endl;
	//file name to save to
	string fileNameSave;
	cout << "enter file to save to -- will save every 10,000 iterations -- adds i for each entire repetition" << endl;
	getline(cin, fileNameSave);

	//generate neural network
	jANN ann(vector<int> {784, 1, 10});
	//ifstream is("meow7");
	//ann.read(is);

	string tmp;

	int iterations = 0;

	while (iterations != 14) {
		cout << "iterations  " << endl;
		int i = 0;
		ifstream is("\\Users\\joeyj\\Downloads\\train.csv");
		if (is.is_open()) {
			cout << "ifstream open to train.csv" << endl;
		}
		else {
			cout << "opening file failed " << endl;
		}
		cout << "moving past first row" << endl;
		getline(is, tmp, '\n');
		try {
			i = 0;
			while (getline(is, tmp, '\n')) {
				ann.train(featureScaling(createInputVector(tmp), 0, 300), createOutputVector(stoi(tmp), 10));
				//++i;
				//cout << i << endl;
				/*
				if (i % 10000 == 0) {
				cout << "saving -- iteration " << i << endl;
				stringstream ss;
				ss << i / 1000;
				ss << "_" << iterations;
				string numb = ss.str();
				string tmp = fileNameSave + numb;

				ofstream os(tmp);
				if (os.is_open()) {
				cout << " saving " << tmp << endl;
				}
				else {
				cout << "file failed to open " << endl;
				}
				ann.write(os);
				os.close();
				}
				*/
			}
			stringstream ss;
			ss << fileNameSave;
			ss << iterations;
			cout << "saving ss - " << ss.str() << endl;
			ofstream os(ss.str());
			ann.write(os);
			os.close();
			is.close();
		}
		catch (...) {
			cout << "reached end of file " << endl;
			is.close();
			stringstream ss;
			ss << fileNameSave;
			ss << iterations;
			cout << "saving ss - " << ss.str() << endl;
			ofstream os(ss.str());
			ann.write(os);
			os.close();
		}
		is.close();
		++iterations;
		cout << iterations << endl;
	}
	cout << "saving " << endl;
	fileNameSave = fileNameSave.append("Fin");
	ofstream os(fileNameSave);
	ann.write(os);
	os.close();
	int wait;
	cin >> wait;
}//??Only trains 7 times till skipping why?????
static void csvTest() {
	//Open training
	cout << "reading from \\Users\\joeyj\\Downloads\\train.csv" << endl;
	//generate neural network
	jANN ann(vector<int> {784, 25, 10});
	ifstream input("DR784_800_10_i4");
	ann.read(input);

	int i = 0;
	ifstream is("\\Users\\joeyj\\Downloads\\train.csv");
	if (is.is_open()) {
		cout << "ifstream open to train.csv" << endl;
	}
	else {
		cout << "opening file failed " << endl;
	}
	cout << "moving past first row" << endl;
	string tmp;
	getline(is, tmp, '\n');
	while (getline(is, tmp, '\n')) {
		cout << " Prediction ---------------------" << endl;
		printEval(ann.predict(featureScaling(createInputVector(tmp), 0, 255)));
		cout << " answer ---------------------" << endl;
		printEval(createOutputVector(stoi(tmp), 10));
	}
}
void submit(string filename) {
	ifstream iFile(filename);
	jANN ann;
	ann.read(iFile);
	iFile.close();

	ofstream os("JJSubmit_" + filename + ".csv");
	os << "ImageId,Label" << '\n';
	ifstream is("\\Users\\joeyj\\Downloads\\test.csv");
	string tmp;
	getline(is, tmp, '\n'); cout << "moved past first row " << endl;
	int i = 0;
	while (getline(is, tmp, '\n')) {
		++i;
		int output = getCorrect(ann.predict(featureScaling(createInputVectorSubmission(tmp), 0, 255)));
		//printEval(ann.predict(featureScaling(createInputVectorSubmission(tmp), 0, 255)));
		os << i << ',' << output << '\n';
	}
	os.close();
	is.close();
}
int main() {
	csvTrain("784_8_10");
}