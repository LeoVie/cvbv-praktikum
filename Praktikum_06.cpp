#include "opencv2/opencv.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/features2d/features2d.hpp"
#include <iostream>
#include "Praktikum_06.h"
#include <string>
#include <chrono>
#include <thread>

using namespace cv;
using namespace std;

namespace praktikum06
{	
    int aufgabe01()
    {
        VideoCapture videoCapture("Daten/Praktikum06/Vid06a.avi");
        Mat frame, modifiedFrame, lastModifiedFrame, differenceFrame;

        while (true) {
            videoCapture >> frame;
            if (frame.empty()) {
                break;
            }

            cvtColor(frame, frame, COLOR_BGR2GRAY);

            equalizeHist(frame, modifiedFrame);
            //blur(frame, modifiedFrame, Size(10, 10));
            //medianBlur(frame, modifiedFrame, 5);

            if (lastModifiedFrame.empty()) {
                modifiedFrame.copyTo(lastModifiedFrame);
            }

            absdiff(modifiedFrame, lastModifiedFrame, differenceFrame);

            imshow("Video", frame);
            imshow("Modified Video", modifiedFrame);
            imshow("Last modified frame", lastModifiedFrame);
            imshow("Difference", differenceFrame);
            int key = waitKey(20);
            if (key == 27) {
                break;
            }

            modifiedFrame.copyTo(lastModifiedFrame);
        }


        waitKey(0);

        return 0;
    }

    int aufgabe02()
    {
        cv::Mat image, warped, rotated;
        image = cv::imread("Daten/Praktikum06/testbild.webp");
        if (!image.data) {
            printf("Error: Couldn't open the image file.\n");
            return 1;
        }

        cv::imshow("Image", image);

        //resizeImage(image);
        //rotateImage(image);
        warpImage(image);

        waitKey(0);

        return 0;
    }

    void resizeImage(Mat& image)
    {
        Mat resized;
        for (int i = 1; i < image.cols; i += 10) {
            for (int j = 1; j < image.rows; j += 10) {
                if (image.cols - i < 0 && image.rows - j < 0) {
                    return;
                }

                resize(image, resized, Size(image.cols - i, image.rows - j));
                imshow("Resized", resized);
                waitKey(1);
            }
        }
    }

    void rotateImage(Mat& image)
    {
        Mat rotated;
        Point center = Point(image.cols / 2, image.rows / 2);
        double scale = 0.6;
        for (double angle = 0; angle <= 360; angle++) {
            Mat rotationMatrix = getRotationMatrix2D(center, angle, scale);
            warpAffine(image, rotated, rotationMatrix, image.size());

            imshow("Rotated", rotated);
            waitKey(1);
        }
    }

    void warpImage(Mat& image)
    {
        Point objectCornerA = Point(6, 250);
        Point objectCornerB = Point(309, 370);
        Point objectCornerC = Point(410, 45);
        Point objectCornerD = Point(220, 17);

        int maxWidth = max(
            distance(objectCornerA, objectCornerD),
            distance(objectCornerB, objectCornerC)
        );

        int maxHeight = max(
            distance(objectCornerA, objectCornerB),
            distance(objectCornerC, objectCornerD)
        );

        vector<Point2f> inputPoints{ objectCornerA, objectCornerB, objectCornerC, objectCornerD };

        vector<Point2f> outputPoints{
            Point2f(0, 0),
            Point2f(0, maxHeight - 1),
            Point2f(maxWidth - 1, maxHeight - 1),
            Point2f(maxWidth - 1, 0)
        };

        Mat m = getPerspectiveTransform(inputPoints, outputPoints);

        Mat warped;
        warpPerspective(image, warped, m, Size(maxWidth, maxHeight));

        imshow("Warped", warped);

        waitKey(0);
    }

    int distance(Point a, Point b)
    {
        return (int)sqrt(pow((a.x - b.x), 2) + pow((a.y - b.y), 2));
    }
}