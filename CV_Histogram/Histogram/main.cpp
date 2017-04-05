#include <iostream>
#include <string>
using namespace std;

#include "opencv2/core/utility.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
using namespace cv;

void drawHistogram(Mat img);
void equalize(Mat img);
void lomography(Mat img);
void cartoon(Mat img);

int main(int argc, const char** argv)
{
    string imgPath = "../../Resource/castle.jpg";
    Mat castle = imread(imgPath, IMREAD_REDUCED_COLOR_2);
    Mat result;

    imshow("Castle", castle);
    //drawHistogram(castle);
    //equalize(castle);
    //lomography(castle);
    cartoon(castle);

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
void lomography(Mat img)
{
    Mat result;
    const float exponential_e = std::exp(1.0);
    // Create Lookup table for color curve effect
    Mat lut(1, 256, CV_8UC1);
    for (int i = 0; i < 256; i++)
    {
        float x = (float)i / 256.0;
        lut.at<uchar>(i) = cvRound(256 * (1 / (1 + pow(exponential_e,-((x - 0.5) / 0.1)))));
    }

    // Split the image channels and apply curve transform only to red channel
    vector<Mat> bgr;
    split(img, bgr);
    LUT(bgr[2], lut, bgr[2]);
    // merge result
    merge(bgr, result);

    // Create image for halo dark
    Mat halo(img.rows, img.cols, CV_32FC3, Scalar(0.3, 0.3, 0.3));
    // Create circle
    circle(halo, Point(img.cols / 2, img.rows / 2), img.cols / 3, Scalar(1, 1, 1), -1);
    blur(halo, halo, Size(img.cols / 3, img.cols / 3));

    // Convert the result to float to allow multiply by 1 factor
    Mat resultf;
    result.convertTo(resultf, CV_32FC3);

    // Multiply result with halo
    multiply(resultf, halo, resultf);

    // Convert to 8 bits
    resultf.convertTo(result, CV_8UC3);

    // show result
    imshow("Lomograpy", result);
}

void cartoon(Mat img)
{
    // Apply median filter to remove possible noise
    Mat imgMedian;
    medianBlur(img, imgMedian, 7);

    // Detect edges with canny
    Mat imgCanny;
    Canny(imgMedian, imgCanny, 50, 150);

    // Dilate the edges
    Mat kernel = getStructuringElement(MORPH_RECT, Size(2, 2));
    dilate(imgCanny, imgCanny, kernel);

    // Scale edges values to 1 and invert values
    imgCanny = imgCanny / 255;
    imgCanny = 1 - imgCanny;

    // Use float values to allow multiply between 0 and 1
    Mat imgCannyf;
    imgCanny.convertTo(imgCannyf, CV_32FC3);

    // Blur the edgest to do smooth effect
    blur(imgCannyf, imgCannyf, Size(5, 5));

    /** COLOR **/
    // Apply bilateral filter to homogenizes color
    Mat imgBF;
    bilateralFilter(img, imgBF, 9, 150.0, 150.0);

    // truncate colors
    Mat result = imgBF / 25;
    result = result * 25;

    /** MERGES COLOR + EDGES **/
    // Create a 3 channles for edges
    Mat imgCanny3c;
    Mat cannyChannels[] = { imgCannyf, imgCannyf, imgCannyf };
    merge(cannyChannels, 3, imgCanny3c);

    // Convert color result to float
    Mat resultf;
    result.convertTo(resultf, CV_32FC3);

    // Multiply color and edges matrices
    multiply(resultf, imgCanny3c, resultf);

    // convert to 8 bits color
    resultf.convertTo(result, CV_8UC3);

    // Show image
    imshow("Result", result);
}