#pragma once

#include "opencv2/opencv.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include <iostream>

using namespace cv;
using namespace std;

namespace praktikum08
{
	int aufgabe01();
	Scalar randColor();
	int randColorPart();
	Point centroid(vector<Point> contour);
	void dilate(Mat image, Mat& destination, int times);
	void erode(Mat image, Mat& destination, int times);
	Mat buildStructuringElement(int size);
	int aufgabe02();
}