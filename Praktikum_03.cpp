#include "opencv2/opencv.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include <iostream>
#include "Praktikum_03.h"

using namespace cv;
using namespace std;

namespace praktikum03
{	
	int aufgabe01()
	{
		Mat image = imread("Daten/Praktikum03/Img03a.jpg");

		imshow("Image", image);
		imshow("Changed channel mapping", shiftChannels(image));
		imshow("Average gray", averageGray(image));

		tuple<Mat, Mat, Mat> singleChannelImages = singleChannels(image);
		imshow("Single gray 0", get<0>(singleChannelImages));
		imshow("Single gray 1", get<1>(singleChannelImages));
		imshow("Single gray 2", get<2>(singleChannelImages));

		imwrite("Daten/Praktikum03/build/first_channel_gray.png", get<0>(singleChannelImages));
		imwrite("Daten/Praktikum03/build/second_channel_gray.jpg", get<1>(singleChannelImages));
		imwrite("Daten/Praktikum03/build/third_channel_gray.bmp", get<2>(singleChannelImages));

		waitKey(0);

		return 0;
	}

	int aufgabe02()
	{
		VideoCapture videoCapture("Daten/Praktikum03/Vid03a.mov");

		int width = videoCapture.get(CAP_PROP_FRAME_WIDTH);
		int height = videoCapture.get(CAP_PROP_FRAME_HEIGHT);

		Mat frame, modifiedFrame;
		int fourcc = VideoWriter::fourcc('M', 'J', 'P', 'G');
		VideoWriter videoWriter("Daten/Praktikum03/build/video.avi", fourcc, 10, Size(width, height));

		while (true) {
			videoCapture >> frame;

			if (frame.empty()) {
				break;
			}

			modifiedFrame = shiftChannels(frame);

			imshow("Video", frame);
			imshow("Modified video", modifiedFrame);

			videoWriter.write(modifiedFrame);

			waitKey(2);
		}

		videoCapture.release();
		videoWriter.release();

		waitKey(0);

		return 0;
	}

	Mat shiftChannels(Mat image)
	{
		Mat modified = image.clone();

		for (int y = 0; y < image.size().height; y++) {
			for (int x = 0; x < image.size().width; x++) {
				for (int c = 0; c < image.channels(); c++) {
					modified.at<Vec3b>(y, x)[c] = image.at<Vec3b>(y, x)[shift(c, 0, image.channels() - 1)];
				}
			}
		}

		return modified;
	}

	int shift(int number, int min, int max)
	{
		int shifted = number + 1;
		if (shifted > max) {
			shifted = min;
		}

		return shifted;
	}

	Mat averageGray(Mat image)
	{
		Mat modified = image.clone();

		for (int y = 0; y < image.size().height; y++) {
			for (int x = 0; x < image.size().width; x++) {
				int sum = 0;
				for (int c = 0; c < image.channels(); c++) {
					sum += image.at<Vec3b>(y, x)[c];
				}
				int average = sum / image.channels();

				for (int c = 0; c < modified.channels(); c++) {
					modified.at<Vec3b>(y, x)[c] = average;
				}
			}
		}

		return modified;
	}

	tuple<Mat, Mat, Mat> singleChannels(Mat image)
	{
		Mat first, second, third;

		first = Mat(image.size(), CV_8U);
		second = first.clone();
		third = first.clone();

		for (int y = 0; y < image.size().height; y++) {
			for (int x = 0; x < image.size().width; x++) {
				first.at<uchar>(y, x) = image.at<Vec3b>(y, x)[0];
				second.at<uchar>(y, x) = image.at<Vec3b>(y, x)[1];
				third.at<uchar>(y, x) = image.at<Vec3b>(y, x)[2];
			}
		}

		return make_tuple(first, second, third);
	}
}