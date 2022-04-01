#pragma once

#include "opencv2/opencv.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include <iostream>

using namespace cv;
using namespace std;

namespace praktikum05
{
	int aufgabe01();
	int aufgabe02();
	Size optimalDFTSize(Mat image);
	Mat createBorder(int optRows, int optCols, Mat image);
	void cropSpectrumIfRowsOrColsAreOdd(Mat& mag);
	void rearrangeQuadrantsToMoveOriginToImageCenter(Mat& mag);
	void switchMats(Mat& i1, Mat& i2);
}