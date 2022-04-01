#include "opencv2/opencv.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/features2d/features2d.hpp"
#include <iostream>
#include "Praktikum_07.h"
#include <string>
#include <chrono>
#include <thread>

using namespace cv;
using namespace std;

namespace praktikum07
{	
    int aufgabe01()
    {
        Mat image, blurred, gray, grad, cornerImage, absGradX, absGradY;

        image = imread("Daten/Praktikum07/Img07a.jpg");
        if (!image.data) {
            printf("Error: Couldn't open the image file.\n");
            return 1;
        }

        // Remove noise by blurring with a Gaussian filter
        Size kernelSize = Size(3, 3);
        double sigmaX = 0;
        GaussianBlur(image, blurred, kernelSize, sigmaX);
        // Convert the image to grayscale
        cvtColor(blurred, gray, COLOR_BGR2GRAY);

        Mat gradX = sobelHorizontal(gray);
        Mat gradY = sobelVertical(gray);

        // converting back to CV_8U
        convertScaleAbs(gradX, absGradX);
        convertScaleAbs(gradY, absGradY);
        addWeighted(absGradX, 0.5, absGradY, 0.5, 0, grad);

        cornerHarris(grad, cornerImage, 7, 5, 0.05);

        imshow("Original", image);
        imshow("Edges", grad);
        imshow("Corners", cornerImage);

        waitKey();
        destroyAllWindows();

        return 0;
    }

    Mat sobelHorizontal(Mat src)
    {
        return sobel(src, (Mat_<char>(3, 3) <<
            -1, 0, 1,
            -2, 0, 2,
            -1, 0, 1));
    }

    Mat sobelVertical(Mat src)
    {
        return sobel(src, (Mat_<char>(3, 3) <<
            -1, -2, -1,
            0, 0, 0,
            1, 2, 1));
    }

    Mat sobel(Mat src, Mat kernel)
    {
        Mat dst;
        filter2D(src, dst, CV_16S, kernel);

        return dst;
    }

    int aufgabe02()
    {
        Mat image1, image2;

        image1 = imread("Daten/Praktikum07/Img07c.jpg", IMREAD_GRAYSCALE);
        if (!image1.data) {
            printf("Error: Couldn't open the image file.\n");
            return 1;
        }
        image2 = imread("Daten/Praktikum07/Img07d.jpg", IMREAD_GRAYSCALE);
        if (!image2.data) {
            printf("Error: Couldn't open the image file.\n");
            return 1;
        }


        int rectWidth = 10, rectHeight = 10;
        Mat rect1 = Mat(image1, Rect(25, 25, rectWidth, rectHeight));
        Mat rect2 = Mat(image1, Rect(70, 70, rectWidth, rectHeight));
        int hbins = 25, sbins = 25;

        MatND lastHist, hist;
        Mat rect;
        double compareValue;
        string compareString;
        printf(" ");
        for (int x = 0; x < image1.size().width - rectWidth; x += rectWidth)
        {
            for (int y = 0; y < image1.size().height - rectHeight; y += rectHeight)
            {
                rect = Mat(image1, Rect(x, y, rectWidth, rectHeight));
                hist = calculateHistForGrayscale(rect, hbins, sbins);
                if (!lastHist.empty())
                {
                    compareValue = compareHist(hist, lastHist, HISTCMP_CORREL);
                    if (compareValue > 0.7)
                    {
                        // aehnlich
                        printf(" ");
                    }
                    else
                    {
                        // unaehnlich
                        printf("-");
                    }
                }
                lastHist = hist;
            }
            printf("\n");
        }

        return 0;
    }

    MatND calculateHistForGrayscale(Mat image, int hbins, int sbins)
    {
        MatND hist;
        int histSize[] = { hbins, sbins };
        // hue varies from 0 to 179
        float hranges[] = { 0, 180 };
        // saturation varies from 0 to 255
        float sranges[] = { 0, 256 };
        const float* ranges[] = { hranges, sranges };

        int channels[] = { 0 };
        int nImages = 1;
        Mat mask = Mat();
        int dims = 1;
        calcHist(&image, nImages, channels, mask, hist, dims, histSize, ranges);

        return hist;
    }
}