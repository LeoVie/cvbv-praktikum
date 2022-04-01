#include "opencv2/opencv.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "Praktikum_01.h"
#include <iostream>

using namespace cv;
using namespace std;

namespace praktikum01 
{
	int aufgabe02()
	{
		Mat image;
		image = imread("Daten/Praktikum01/Img01a.jpg");
		if (!image.data) {
			printf("Error: Couldn't open the image file.\n");
			return 1;
		}
		cv::namedWindow("Image:");
		cv::imshow("Image:", image);
		cv::waitKey(0);
		cv::destroyWindow("Image:");
		return 0;
	}


	int aufgabe03()
	{
		Mat originalImage = imread("Daten/Praktikum01/Img01a.jpg");
		if (!originalImage.data) {
			printf("Error: Couldn't open the image file.\n");
			return 1;
		}

		Mat modifiedImage = originalImage.clone();

		Mat modifiedImageHsv;
		cvtColor(modifiedImage, modifiedImageHsv, COLOR_BGR2HSV);
		map<string, int> constantBrightnessRectangle{
			{ "top", 20 },
			{ "left", 20 },
			{ "width", 500 },
			{ "height", 200 }
		};
		int brightness = 100;
		for (int y = constantBrightnessRectangle["top"]; y < constantBrightnessRectangle["top"] + constantBrightnessRectangle["height"]; y++) {
			for (int x = constantBrightnessRectangle["left"]; x < constantBrightnessRectangle["left"] + constantBrightnessRectangle["width"]; x++) {
				modifiedImageHsv.at<Vec3b>(y, x)[2] = saturate_cast<uchar>(brightness);
			}
		}
		cvtColor(modifiedImageHsv, modifiedImage, COLOR_HSV2BGR);
		putText(modifiedImage, "Constant brightness", Point(constantBrightnessRectangle["left"], constantBrightnessRectangle["top"] + constantBrightnessRectangle["height"] / 2), FONT_HERSHEY_DUPLEX, 1, Scalar(255, 0, 0));

		map<string, int> averageRectangle{
			{ "top", constantBrightnessRectangle["top"] + 200 + 20 },
			{ "left", 20 },
			{ "width", 500 },
			{ "height", 200 }
		};
		for (int y = averageRectangle["top"]; y < averageRectangle["top"] + averageRectangle["height"]; y++) {
			for (int x = averageRectangle["left"]; x < averageRectangle["left"] + averageRectangle["width"]; x++) {
				for (int c = 0; c < originalImage.channels(); c++) {
					int average = (int)(originalImage.at<Vec3b>(y, x - 1)[c] + originalImage.at<Vec3b>(y, x)[c]) / 2;
					modifiedImage.at<Vec3b>(y, x)[c] = saturate_cast<uchar>(average);
				}
			}
		}
		putText(modifiedImage, "Average", Point(averageRectangle["left"], averageRectangle["top"] + averageRectangle["height"] / 2), FONT_HERSHEY_DUPLEX, 1, Scalar(255, 0, 0));

		map<string, int> differenceRectangle{
			{ "top", averageRectangle["top"] + 200 + 20 },
			{ "left", 20 },
			{ "width", 500 },
			{ "height", 200 }
		};
		for (int y = differenceRectangle["top"]; y < differenceRectangle["top"] + differenceRectangle["height"]; y++) {
			for (int x = differenceRectangle["left"]; x < differenceRectangle["left"] + differenceRectangle["width"]; x++) {
				for (int c = 0; c < originalImage.channels(); c++) {
					int average = (originalImage.at<Vec3b>(y, x - 1)[c] - originalImage.at<Vec3b>(y, x)[c]);
					modifiedImage.at<Vec3b>(y, x)[c] = saturate_cast<uchar>(average);
				}
			}
		}
		putText(modifiedImage, "Difference", Point(differenceRectangle["left"], differenceRectangle["top"] + differenceRectangle["height"] / 2), FONT_HERSHEY_DUPLEX, 1, Scalar(255, 0, 0));

		cv::imshow("Original Image:", originalImage);
		cv::imshow("Modified image:", modifiedImage);
		cv::waitKey(0);
		return 0;
	}
}