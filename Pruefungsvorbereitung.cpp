#include "opencv2/opencv.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "pruefungsvorbereitung.h"

using namespace cv;
using namespace std;

namespace pruefungsvorbereitung
{
	int aufgabe01()
	{
		Mat image, blured, dif;
		vector<Mat> channels;

		image = imread("Daten/pruefungsvorbereitung/img.jpg");
		split(image, channels);
		GaussianBlur(channels[0], blured, Size(9, 9), 5);
		absdiff(channels[0], blured, dif);
		imshow("Channel 0 diff", dif);

		waitKey(0);

		return 0;
	}
}