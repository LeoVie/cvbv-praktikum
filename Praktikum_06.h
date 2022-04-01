#pragma once

#include "opencv2/opencv.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include <iostream>

using namespace cv;
using namespace std;

namespace praktikum06
{
	int aufgabe01();
	int aufgabe02();
	void resizeImage(Mat& image);
	void rotateImage(Mat& image);
	void warpImage(Mat& image);
	int distance(Point a, Point b);
}