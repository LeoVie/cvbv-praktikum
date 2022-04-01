#include "opencv2/opencv.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/features2d/features2d.hpp"
#include <iostream>
#include "Praktikum_09.h"
#include <string>
#include <chrono>
#include <thread>

using namespace cv;
using namespace std;

namespace praktikum09
{	
    int aufgabe01()
    {
        return 0;
    }

    int aufgabe02()
    {
        Mat image, image1, image2, homography, map1, cameraMatrix, distCoeffs;
        int flag = 0;
        Size boardSize(7, 7);
        vector<Point3f> objectCorners;
        vector<Point2f> imageCorners, object4Corners(4), image4Corners(4);
        vector<vector<Point3f>> objectPoints;
        vector<vector<Point2f>> imagePoints;
        vector<Mat> rvecs, tvecs;

        for (int i = 0; i < boardSize.height; i++)
        {
            for (int j = 0; j < boardSize.width; j++)
            {
                objectCorners.push_back(Point3f(i, j, 0.0f));
            }
        }


        image = imread("Daten/Praktikum09/Img09c10.jpg");
        if (!image.data) {
            printf("Error: Couldn't open the image file.\n");
            return 1;
        }
        bool patternWasFound = findChessboardCorners(image, boardSize, imageCorners);
        if (patternWasFound)
        {
            printf("Pattern was found\n");
        }
        else
        {
            printf("Pattern was not found\n");
        }

        drawChessboardCorners(image, boardSize, imageCorners, patternWasFound);
        objectPoints.push_back(objectCorners);
        imagePoints.push_back(imageCorners);

        cv::imshow("Image", image);
        cv::waitKey(0);
        cv::destroyAllWindows();

        /*
        for (int i = 1; i < 7; i++)
        {
            char imgName[20] = "a";
            image = imread(imgName);
            findChessboardCorners(image, boardSize, imageCorners);
            drawChessboardCorners(image, boardSize, imageCorners, true);
            objectPoints.push_back(objectCorners);
            imagePoints.push_back(imageCorners);
        }
        calibrateCamera(objectPoints, imagePoints, image.size(), cameraMatrix, distCoeffs, rvecs, tvecs, flag);
        undistort(image, image1, cameraMatrix, distCoeffs, map1);
        object4Corners = objectCorners...;
        image4Corners = imageCorners...;
        homography = getPerspectiveTransform(image4Corners, object4Corners);
        warpPerspective(image, image2, homography, Size(image.cols * 1, image.rows * 2));
        int x = 0;
        int y = 0;
        Mat mp1(1, 1, CV_32FC2, Scalar(x, y)), mp2;
        perspectiveTransform(mp1, mp2, homography);
        x = mp2.at<Point2f>(0, 0)[0];
        y = mp2.at<Point2f>(0, 0)[1];
        */

        return 0;
    }
}