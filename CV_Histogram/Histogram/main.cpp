#include <iostream>
#include <string>
using namespace std;

#include "opencv2/core/utility.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
using namespace cv;

void drawHistogram(Mat img);
void equalize(Mat img);

int main(int argc, const char** argv)
{
    string imgPath = "../../Resource/castle.jpg";
    Mat castle = imread(imgPath, IMREAD_REDUCED_COLOR_2);
    Mat result;

    imshow("Castle", castle);
    drawHistogram(castle);
    equalize(castle);

    waitKey(0);
    return 1;
}

void drawHistogram(Mat img) {
    vector<Mat> bgr;
    split(img, bgr);

    // Create the histogram for 256 bins
    int numbins = 256;

    // Set the range
    float range[] = { 0 , 256 };
    const float* histRange = { range };

    Mat b_hist, g_hist, r_hist;

    calcHist(&bgr[0], 1, 0, Mat(), b_hist, 1, &numbins,
        &histRange);
    calcHist(&bgr[1], 1, 0, Mat(), g_hist, 1, &numbins,
        &histRange);
    calcHist(&bgr[2], 1, 0, Mat(), r_hist, 1, &numbins,
        &histRange);

    // Draw line for each channel
    int width = 512;
    int height = 300;

    // Create image with gray base
    Mat histImage(height, width, CV_8UC3, Scalar(20, 20, 20));

    // Normalize the historgrams to height of image
    normalize(b_hist, b_hist, 0, height, NORM_MINMAX);
    normalize(g_hist, g_hist, 0, height, NORM_MINMAX);
    normalize(r_hist, r_hist, 0, height, NORM_MINMAX);

    int binStep = cvRound((float)width / (float)numbins);
    for (int i = 1; i< numbins; i++)
    {
        line(histImage,
            Point(binStep*(i - 1), height - cvRound(b_hist.at<float>(i - 1))),
            Point(binStep*(i), height - cvRound(b_hist.at<float>(i))),
            Scalar(255, 0, 0));
        line(histImage,
            Point(binStep*(i - 1), height - cvRound(g_hist.at<float>(i - 1))),
            Point(binStep*(i), height - cvRound(g_hist.at<float>(i))),
            Scalar(0, 255, 0));
        line(histImage,
            Point(binStep*(i - 1), height - cvRound(r_hist.at<float>(i - 1))),
            Point(binStep*(i), height - cvRound(r_hist.at<float>(i))),
            Scalar(0, 0, 255));
    }
    imshow("Histogram", histImage);

}

void equalize(Mat img) 
{
    Mat result;
    // Convert BGF image to YCbCr
    Mat ycrcb;
    cvtColor(img, ycrcb, COLOR_BGR2YCrCb);

    // Split image into channels
    vector<Mat> channels;
    split(ycrcb, channels);

    // Equalize the Y channel only
    equalizeHist(channels[0], channels[0]);

    // Merge the result channels
    merge(channels, ycrcb);

    // Convert color ycrcb to BGR
    cvtColor(ycrcb, result, COLOR_YCrCb2BGR);

    // Show image
    imshow("Equalized", result);

}