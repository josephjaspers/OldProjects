#pragma once
#ifndef Point_H
#define Point_H
#include <vector>
using namespace std;
class Point {

	vector<double> data = vector<double>(0);
	int features;
	int clusterIndex;

public: 
	Point::Point(const vector<double> &data) {
		Point::data = data; 
		features = data.size();
	}
	Point::Point(int feat) {
		features = feat;
		data = vector<double>(features);
	}
	Point::Point() {
		features = 0;
	}

	Point::Point(const Point &p) {
		features = p.features;
		data = p.data; 
	}
	double distance(const Point &p) {
		double dist = 0;
		for (int i = 0; i < p.data.size(); ++i) {
			dist += abs(data[i] - p.data[i]);
		}
		return dist;
	}
	void setClusterIndex(int index) {
		clusterIndex = index;
	}
	int getClusterIndex() {
		return clusterIndex;
	}
	vector<double>& getData() {
		return data;
	}
	void updateData(vector<double> &update) {
		if (update.size() != data.size()) {
			throw exception("invalid data / size mismatch");
		}
		data = update;
	}
	void clearData() {
		data = vector<double>(data.size());
	}
private:

};
#endif
