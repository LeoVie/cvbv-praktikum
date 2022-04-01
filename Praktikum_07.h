#pragma once

#include "opencv2/opencv.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include <iostream>

using namespace cv;
using namespace std;

namespace praktikum07
{
	int aufgabe01();
	Mat sobelHorizontal(Mat src);
	Mat sobelVertical(Mat src);
	Mat sobel(Mat src, Mat kernel);
	int aufgabe02();
	MatND calculateHistForGrayscale(Mat image, int hbins, int sbins);
}