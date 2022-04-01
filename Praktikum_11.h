#pragma once

#include "opencv2/opencv.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include <iostream>

using namespace cv;
using namespace std;

namespace praktikum11
{
	int aufgabe01();
	Mat nextFrame(VideoCapture c);
	Mat toGrayscale(Mat i);
	vector<Scalar> randColors(int n);
	Scalar randColor();
	int randColorPart();
	int aufgabe02();
	void maxHueChange();
	Mat extractHueChannel(Mat rgb);
	Mat rgbToHsv(Mat rgb);
}