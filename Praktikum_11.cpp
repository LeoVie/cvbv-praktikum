#include "opencv2/opencv.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "Praktikum_11.h"

using namespace cv;
using namespace std;

namespace praktikum11
{
    RNG rng;

    int aufgabe01()
    {
        VideoCapture capture("Daten/Praktikum11/Vid11a.mpg");
        //VideoCapture capture("Daten/Praktikum11/Vid11c.mpg");
        //VideoCapture capture("Daten/Praktikum11/Vid11d.avi");
        if (!capture.isOpened())
        {
            printf("Error opening video file.\n");
            return 1;
        }

        vector<Scalar> colors = randColors(100);

        vector<Point2f> lastCorners;

        // Take first frame and find corners in it
        Mat oldFrame = nextFrame(capture);
        Mat lastFrameGray = toGrayscale(oldFrame);

        int maxCorners = 100;
        double qualityLevel = 0.3;
        double minDistance = 7;
        int blockSize = 7;
        goodFeaturesToTrack(lastFrameGray, lastCorners, maxCorners, qualityLevel, minDistance, Mat(), blockSize);

        Mat mask = Mat::zeros(oldFrame.size(), oldFrame.type());
        while (true)
        {
            Mat frame = nextFrame(capture);
            if (frame.empty())
            {
                break;
            }
            Mat frameGray = toGrayscale(frame);

            // calculate optical flow
            vector<Point2f> corners;
            vector <uchar> status;
            vector<float> error;
            Size winSize = Size(15, 15);
            int maxLevel = 2;
            int maxCount = 10;
            double epsilon = 0.03;
            TermCriteria criteria = TermCriteria((TermCriteria::COUNT) + (TermCriteria::EPS), maxCount, epsilon);
            calcOpticalFlowPyrLK(lastFrameGray, frameGray, lastCorners, corners, status, error, winSize, maxLevel, criteria);

            vector<Point2f> goodCorners;
            for (uint i = 0; i < lastCorners.size(); i++)
            {
                // Select good points
                if (status[i] == 1)
                {
                    goodCorners.push_back((corners[i]));
                    // draw the tracks
                    arrowedLine(mask, corners[i], lastCorners[i], colors[i], 2);
                }
            }

            Mat img;
            add(frame, mask, img);
            imshow("Frame", img);

            lastFrameGray = frameGray;
            lastCorners = goodCorners;

            waitKey();
        }


        return 0;
    }

    Mat nextFrame(VideoCapture c)
    {
        Mat f;
        c >> f;

        return f;
    }

    Mat toGrayscale(Mat i)
    {
        Mat g;
        cvtColor(i, g, COLOR_BGR2GRAY);

        return g;
    }

    vector<Scalar> randColors(int n)
    {
        vector<Scalar> colors;
        for (int i = 0; i < 100; i++)
        {
            colors.push_back(randColor());
        }

        return colors;
    }

    Scalar randColor()
    {
        return Scalar(randColorPart(), randColorPart(), randColorPart());
    }

    int randColorPart()
    {
        return rng.uniform(0, 256);
    }

    int aufgabe02()
    {
        maxHueChange();
        
        /*
        KalmanFilter KF(4, 4, 0);
        Mat state(4, 1, CV_32F);
        Mat trans(4, 4, CV_32F);
        Mat processNoise(2, 1, CV_32F);
        Mat measurement = Mat::zeros(4, 1, CV_32F);
        Mat frame, frame1, frame2, wholeFrame;
        vector<Mat> planes;
        Point2f objcenter(0, 0);

        VideoCapture capture("Daten/Praktikum11/Vid11d.avi");

        capture >> wholeFrame;

        Rect rect = Rect(20, 20, 300, 150);

        frame = wholeFrame(rect);

        split(frame, planes);
        frame1 = planes[1];
        state = (Mat_<float>(4, 1) << 100, 100, 10, -10);
        trans = (Mat_<float>(4, 4) << 1, 0, 1, 0, 0, 1, 0, 1, 0, 0, 1, 0, 0, 0, 0, 1);
        KF.transitionMatrix = trans;
        setIdentity(KF.measurementMatrix);
        setIdentity(KF.processNoiseCov, Scalar::all(1e-5));
        setIdentity(KF.measurementNoiseCov, Scalar::all(1e-1));
        setIdentity(KF.errorCovPost, Scalar::all(1));
        setIdentity(KF.statePost, Scalar::all(0));

        Mat mask = Mat::zeros(frame.size(), frame.type());

        while (true)
        {
            frame1.copyTo(frame2);
            capture >> wholeFrame;
            if (wholeFrame.empty())
            {
                break;
            }

            Mat frame = wholeFrame(rect);

            split(frame, planes);
            frame1 = planes[1];

            Mat prediction = KF.predict();
            Point predictPt = Point2f(prediction.at<float>(0), prediction.at<float>(1));

            printf("Center: (%d, %d)\n", predictPt.x, predictPt.y);
            //printf("Center\n");
            circle(mask, predictPt, 50, Scalar(255, 0, 0));

            Point predictVl = Point2f(prediction.at<float>(2), prediction.at<float>(3));
            measurement = (Mat_<float>(4, 1) << objcenter.x, objcenter.y, 5, 0);
            KF.correct(measurement);

            Mat img;
            cv::add(frame, mask, img);
            cv::imshow("Frame", img);

            int keyboard = waitKey(30);
            if (keyboard == 'q' || keyboard == 27)
            {
                break;
            }
        }
        */

        return 0;     
    }

    void maxHueChange()
    {
        VideoCapture capture("Daten/Praktikum11/Vid11d.avi");
        Mat lastFrame = nextFrame(capture);

        vector<Mat> absDiffs;
        Mat totalAbsDiff = Mat::zeros(lastFrame.size(), CV_8UC1);
        while (true)
        {
            Mat frame = nextFrame(capture);
            if (frame.empty()) {
                break;
            }

            Mat absDiff;
            absdiff(extractHueChannel(frame), extractHueChannel(lastFrame), absDiff);
            absDiffs.push_back(absDiff);

            lastFrame = frame;
        }

        Point maxChangePoint;
        int maxChange = 0;
        for (int x = 0; x < absDiffs[0].cols; x++) {
            for (int y = 0; y < absDiffs[0].rows; y++) {
                int changesSum = 0;
                for (int i = 0; i < absDiffs.size(); i++) {
                    int change = absDiffs[i].at<uchar>(y, x);
                    changesSum += change;
                }

                if (changesSum > maxChange)
                {
                    maxChange = changesSum;
                    maxChangePoint = Point(x, y);
                }
            }
        }

        VideoCapture capture2("Daten/Praktikum11/Vid11d.avi");
        while (true) {
            Mat frame = nextFrame(capture2);
            if (frame.empty()) {
                break;
            }

            circle(frame, maxChangePoint, 5, Scalar(255, 0, 0));
            imshow("Frame", frame);

            waitKey(0);
        }
    }

    Mat extractHueChannel(Mat rgb)
    {
        vector<Mat> channels;

        split(rgbToHsv(rgb), channels);

        return channels[0];
    }

    Mat rgbToHsv(Mat rgb)
    {
        Mat hsv;

        cvtColor(rgb, hsv, COLOR_BGR2HSV);

        return hsv;
    }
}