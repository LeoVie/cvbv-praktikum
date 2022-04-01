#pragma once

#include "opencv2/opencv.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include <iostream>

using namespace cv;
using namespace std;

namespace praktikum02
{
	int aufgabe01();
	Mat negative(Mat image);
	void toggleNegative(Mat image);
	int aufgabe02();
	void showImage(Mat image);
	void showControl(Mat control);
	void resetControl();
	void onMouse(int event, int x, int y, int flags, void* userdata);
	void onLButtonDown(int x, int y);
	void onContrastChange(int pos, void* userdata);
	void onBrightnessChange(int pos, void* userdata);
	Mat changeContrastAndBrightness();
}