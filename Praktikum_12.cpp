#include "opencv2/opencv.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "Praktikum_12.h"

using namespace cv;
using namespace std;

namespace praktikum12
{
    int aufgabe01()
    {
		Mat image, imageKanal01, imageKanal02, imageKanal03, imageThreshold01, imageThreshold02, imageThreshold03, imageErode01, imageErode02, imageErode03;
		Mat imageDilate01, imageDilate02, imageDilate03, distance01, distance02, distance03;

		// Original lesen
		image = imread("Daten/Praktikum12/Img12a.jpg");
		if (image.empty()) {
			cout << "Originalbild nicht vorhanden" << endl;
			return -1;
		}

		double sum = 0;
		for (int i = 0; i < image.rows; i++) {
			for (int j = 0; j < image.cols; j++) {
				sum += image.at<Vec3b>(i, j)[0];
			}
		}
		printf("Sum 1: %f\n", sum);

		sum = 0;
		for (int i = 0; i < image.rows; i++) {
			const Vec3b* mi = image.ptr<Vec3b>(i);
			for (int j = 0; j < image.cols; j++) {
				sum += mi[j][0];
			}
		}

		printf("Sum 2: %f\n", sum);
		return 0;


		imshow("Original", image);

		vector<cv::Mat> planes;
		split(image, planes); //imageOriginal splitten auf die verschiedenen Kan‰le

		cout << image.size() << endl;

		imageKanal01 = planes[0];
		imageKanal02 = planes[1];
		imageKanal03 = planes[2];

		imshow("Kanal 1", imageKanal01);
		imshow("Kanal 2", imageKanal02);
		imshow("Kanal 3", imageKanal03);

		// Threshold verwenden
		// evtl. mit Schiebereglern arbeiten
		int tresh = 75; //ab welchen Wert soll Farbe abgeschnitten werden? - 0 => Schwarz, 255 => weiﬂ
		double treshMaxValue = 255;

		createTrackbar("Threshold", "Original", &tresh, 255); //Trackbar erstellen

		while (true)
		{
			threshold(imageKanal01, imageThreshold01, tresh, treshMaxValue, THRESH_BINARY_INV); //invertierter Threshold
			threshold(imageKanal02, imageThreshold02, tresh, treshMaxValue, THRESH_BINARY_INV); //invertierter Threshold
			threshold(imageKanal03, imageThreshold03, tresh, treshMaxValue, THRESH_BINARY_INV); //invertierter Threshold

			imshow("Threshold01 invertiert", imageThreshold01);
			imshow("Threshold02 invertiert", imageThreshold02);
			imshow("Threshold03 invertiert", imageThreshold03);

			// solange warten, bis ESC gedrueckt wurde
			int auswahl = waitKey(50);
			if (auswahl == 27) // ESCAPE
			{
				break;
			}

		}

		waitKey();

		// erode verwenden (erode --> aushˆhlen)
		// evtl. mit Schiebereglern arbeiten
		erode(imageThreshold01, imageErode01, Mat(), Point(-1, -1), 2);
		erode(imageThreshold02, imageErode02, Mat(), Point(-1, -1), 2);
		erode(imageThreshold03, imageErode03, Mat(), Point(-1, -1), 2);

		imshow("Erode aus Threshold01", imageErode01);
		imshow("Erode aus Threshold02", imageErode02);
		imshow("Erode aus Threshold03", imageErode03);

		waitKey();
		// dilate verwenden (dilate --> erweitern) --> glaetten der gefundenen Punkte
		dilate(imageThreshold01, imageDilate01, Mat(), Point(-1, -1), 5);
		dilate(imageThreshold02, imageDilate02, Mat(), Point(-1, -1), 5);
		dilate(imageThreshold03, imageDilate03, Mat(), Point(-1, -1), 5);

		imshow("Dilate aus invertierten Threshold01", imageDilate01);
		imshow("Dilate aus invertierten Threshold02", imageDilate02);
		imshow("Dilate aus invertierten Threshold03", imageDilate03);

		// distanceTransform
	//	cvtColor(imageDilate01, imageDilate01, COLOR_BGR2GRAY);
		distanceTransform(imageDilate01, distance01, DIST_L2, 3);
		normalize(distance01, distance01, 0, 1.0, NORM_MINMAX);
		imshow("Distance01", distance01);


		// Konturen, Rechtecke und ConvHull finden
		// https://docs.opencv.org/3.4/d4/d40/samples_2cpp_2watershed_8cpp-example.html
		// https://stackoverflow.com/questions/8449378/finding-contours-in-opencv#8467129
		vector<vector<Point>> contours;
		findContours(imageDilate01, contours, RETR_CCOMP, CHAIN_APPROX_NONE);

		Mat imageContours(imageDilate01.size(), CV_8UC1, Scalar(0, 0, 0)); //8U --> 8 Bit, unsigned ..C1 --> 1 Kanal 
		// https://stackoverflow.com/questions/27183946/what-does-cv-8uc3-and-the-other-types-stand-for-in-opencv zu CV_8UC1 und anderen
		//Mat imageContours(imageDilate.size(), CV_8UC3, Scalar(0, 0, 0)); //Mehrfarbig
		Scalar colors(255, 0, 255);

		imshow("Konturen", imageContours);


		// alles schlieﬂen
		waitKey();
		destroyAllWindows();

		return 0;
    }
}