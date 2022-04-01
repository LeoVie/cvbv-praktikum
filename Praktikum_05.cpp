#include "opencv2/opencv.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/features2d/features2d.hpp"
#include <iostream>
#include "Praktikum_05.h"
#include <string> 

using namespace cv;
using namespace std;

namespace praktikum05
{	
    int aufgabe01()
    {
        Mat image = imread("Daten/Praktikum05/Img05a.jpg", IMREAD_GRAYSCALE);

        imshow("Image", image);

        Mat hist;
        int rectCount = 64;
        calcHist(&image, 1, 0, Mat(), hist, 1, &rectCount, 0);

        Mat histImage = Mat::ones(200, 320, CV_8U) * 255;

        normalize(hist, hist, 0, histImage.rows, NORM_MINMAX, CV_32F);

        int rectWidth = cvRound((double)(histImage.cols / rectCount));

        Scalar black = Scalar::all(0);
        for (int i = 0; i < rectCount; i++) {
            Point point1 = Point(i * rectWidth, histImage.rows);
            int x = (i + 1) * rectWidth;
            int y = histImage.rows - cvRound(hist.at<float>(i));
            Point point2 = Point(x, y);
            rectangle(histImage, point1, point2, black);
        }

        imshow("Histogram", histImage);

        waitKey(0);

        vector<cv::Mat> gaussImages;
        Mat srcGauss;
        image.copyTo(srcGauss);

        int layer = 0;
        while (srcGauss.cols > 1)
        {
            pyrDown(srcGauss, srcGauss, srcGauss.size() / 2);
            gaussImages.push_back(srcGauss);
            imshow("Gauss " + layer, srcGauss);
            layer++;
        }

        waitKey(0);

        vector<cv::Mat> laplaceImages;
        Mat srcLaplace, down, up, laplace;
        image.copyTo(srcLaplace);

        layer = 0;
        while (srcLaplace.cols > 1) 
        {
            pyrDown(srcLaplace, down, srcLaplace.size() / 2);
            pyrUp(down, up, srcLaplace.size());

            laplace = srcLaplace - up;
            laplaceImages.push_back(laplace);

            srcLaplace = down;

            imshow("Laplace " + layer, srcLaplace);

            layer++;
        }

        waitKey(0);

        return 0;
    }

    int aufgabe02()
    {
        Mat image = imread("Daten/Praktikum05/Img05a.jpg", IMREAD_GRAYSCALE);
        //Mat image = cv::imread("Daten/Praktikum05/schwarzer_schraeger_strich.png", cv::IMREAD_GRAYSCALE);
        

        // Fourier
        Size optSize = optimalDFTSize(image);

        vector<Mat> planes;
        planes.push_back(createBorder(optSize.height, optSize.width, image));
        planes.push_back(Mat::zeros(planes[0].rows, planes[0].cols, CV_32F));

        Mat complexI = Mat();
        merge(planes, complexI);

        // Discrete Fourier Transformation
        dft(complexI, complexI);

        // compute log(1 + sqrt(Re(DFT(img))**2 + Im(DFT(img))**2))
        split(complexI, planes);
        Mat fourierImage;
        magnitude(planes[0], planes[1], fourierImage);
        Mat one = Mat::ones(fourierImage.size(), fourierImage.type());
        add(one, fourierImage, fourierImage);
        log(fourierImage, fourierImage);

        cropSpectrumIfRowsOrColsAreOdd(fourierImage);
        rearrangeQuadrantsToMoveOriginToImageCenter(fourierImage);

        // The pixel value of cv.CV_32S type image ranges from 0 to 1.
        normalize(fourierImage, fourierImage, 0, 1, NORM_MINMAX);

        imshow("Image", image);
        imshow("Fourier", fourierImage);

        waitKey(0);

        return 0;
    }

    Size optimalDFTSize(Mat i)
    {
        return Size(getOptimalDFTSize(i.cols), getOptimalDFTSize(i.rows));
    }

    Mat createBorder(int optRows, int optCols, Mat image)
    {
        int top = 0;
        int bottom = optRows - image.rows;
        int left = 0;
        int right = optCols - image.cols;

        Mat padded = Mat();
        copyMakeBorder(image, padded, top, bottom, left, right, cv::BORDER_CONSTANT);

        Mat plane = Mat();
        padded.convertTo(plane, CV_32F);

        return plane;
    }

    void cropSpectrumIfRowsOrColsAreOdd(Mat& m)
    {
        Rect(0, 0, m.cols & -2, m.rows & -2);
    }

    void rearrangeQuadrantsToMoveOriginToImageCenter(Mat& m)
    {
        float xCenter = m.cols / 2;
        float yCenter = m.rows / 2;

        Mat q1 = m(Rect(0, 0, xCenter, yCenter));
        Mat q2 = m(Rect(xCenter, 0, xCenter, yCenter));
        Mat q3 = m(Rect(0, yCenter, xCenter, yCenter));
        Mat q4 = m(Rect(xCenter, yCenter, xCenter, yCenter));

        switchMats(q1, q4);
        switchMats(q2, q3);
    }

    void switchMats(Mat& i1, Mat& i2)
    {
        Mat tmp = i1.clone();
        i2.copyTo(i1);
        tmp.copyTo(i2);
    }
}