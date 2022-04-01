#define _CRT_SECURE_NO_WARNINGS
#include "opencv2/opencv.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include <iostream>
#include "Praktikum_02.h"

using namespace cv;
using namespace std;

namespace praktikum02
{
	const int keyQ = 113;
	const int keyW = 119;

	Mat image, control;
	int contrast = 1;
	int brightness = 1;
	Point startPoint, endPoint;

	int aufgabe01()
	{
		image = imread("Daten/Praktikum02/Img02.jpg", IMREAD_GRAYSCALE);

		imshow("Image", image);

		printf("Zeilen: %d, Spalten: %d\n", image.rows, image.cols);

		double minimum, maximum;
		minMaxLoc(image, &minimum, &maximum);
		printf("Minimum: %f, Maximum: %f\n", minimum, maximum);

		Scalar meanOfImage, meanStdDevOfImage;
		meanStdDev(image, meanOfImage, meanStdDevOfImage);
		printf("Mittelwert: %f\n", meanOfImage[0]);
		printf("Standardabweichung: %f\n", meanStdDevOfImage[0]);

		toggleNegative(image);
		
		destroyWindow("Image");

		return 0;
	}

	void toggleNegative(Mat image)
	{
		while (true) {
			int key = waitKey(0);

			switch (key)
			{
				case keyQ:
					return;
				case keyW:
					image = negative(image);
					imshow("Image", image);
					break;
			}
		}
	}

	Mat negative(Mat image)
	{
		return 255 - image;
	}

	int aufgabe02()
	{
		image = imread("Daten/Praktikum02/Img02.jpg");
		showImage(image);

		resetControl();
		setMouseCallback("Image", onMouse, &image);

		createTrackbar("Contrast", "Control", &contrast, 10, onContrastChange);
		createTrackbar("Brightness", "Control", &brightness, 255, onBrightnessChange);

		waitKey(0);

		Rect roi = selectROI(image);
		imshow("ROI", image(roi));

		waitKey(0);

		destroyWindow("Image");
		destroyWindow("Control");

		return 0;
	}

	void showImage(Mat image)
	{
		imshow("Image", image);
	}

	void showControl(Mat control)
	{
		imshow("Control", control);
	}

	void resetControl()
	{
		control = Mat(image.rows, image.cols, CV_8UC1, Scalar(70));
		showControl(control);
	}

	void onMouse(int event, int x, int y, int flags, void* userdata)
	{
		if (event == MouseEventTypes::EVENT_LBUTTONDOWN) {
			onLButtonDown(x, y);
		}
	}

	void onLButtonDown(int x, int y)
	{
		printf("x: %d, y: %d\n", x, y);

		Vec3b position = image.at<Vec3b>(y, x);

		printf("Farbwerte: (%d, %d, %d, %d)\n", position[0], position[1], position[2], position[3]);

		circle(image, Point(x, y), 10, Scalar(255, 0, 0));
		showImage(image);

		char output[15];
		sprintf(output, "x: %d, y: %d", x, y);

		resetControl();
		putText(control, output, Point(10, 30), FONT_HERSHEY_TRIPLEX, 1, Scalar(255, 255, 255));
		showControl(control);
	}

	void onContrastChange(int pos, void* userdata)
	{
		if (pos == 0) {
			contrast = 1;
			return;
		}

		contrast = pos;
		showImage(changeContrastAndBrightness());
	}

	void onBrightnessChange(int pos, void* userdata)
	{
		brightness = pos;
		showImage(changeContrastAndBrightness());
	}

	Mat changeContrastAndBrightness()
	{
		Mat newImage;

		image.convertTo(newImage, -1, contrast, brightness);

		return newImage;
	}
}