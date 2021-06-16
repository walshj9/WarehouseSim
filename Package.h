#include <string>
#include <ctime>
#include <vector>
#pragma once

using namespace std;

class Package {

public:

	Package() { ; }//default constructor

	Package(double  pkg_height, double  pkg_width, double  pkg_length, double  pkg_weight, bool  pkg_OV, string TBAnum, string stow) {//constructor
		height = pkg_height;
		width = pkg_width;
		length = pkg_length;
		weight = pkg_weight;
		isOV = pkg_OV;
		trackingNum = TBAnum;
	}

	double  getWeight() { return weight; }
	double getHeight() { return height; }
	double getWidth() { return width; }
	double getLength() { return length; }
	string  getTBAnum() { return trackingNum; }
	bool isOverSize() { return isOV; }

	double pkgVolume(double a, double b, double c) { return a * b * c; }


	bool determneOV(Package p) {
		if (p.getWeight() >= 11.0) {
			return true;
		}
		return false;
	}

private:
	double height, width, length, weight; //attribute
	bool isOV; //attribute
	string trackingNum, stow_location;

};