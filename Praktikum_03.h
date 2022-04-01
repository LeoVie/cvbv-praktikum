#pragma once

#include "opencv2/opencv.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include <iostream>

using namespace cv;
using namespace std;

namespace praktikum03
{
	int aufgabe01();
	int aufgabe02();
	Mat shiftChannels(Mat image);
	int shift(int number, int min, int max);
	Mat averageGray(Mat image);
	tuple<Mat, Mat, Mat> singleChannels(Mat image);
}