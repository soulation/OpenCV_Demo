#include <iostream>
#include <string>
#include <sstream>

// OpenCV includes
#include "opencv2/core.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
using namespace cv;

static void onChange(int pos, void* userInput);
static void onMouse(int event, int x, int y, int, void* userInput);
int blurAmount = 15;

int main(int argc, const char** argv)
{

    // Read images
    Mat castle = imread("castle.jpg");

    // Create windows
    namedWindow("Castle", CV_WINDOW_AUTOSIZE);

    // Create track bar
    createTrackbar("Castle", "Castle", &blurAmount, 30, onChange, &castle);
    setMouseCallback("Castle", onMouse, &castle);

    // Call to onChange to init
    onChange(blurAmount, &castle);

    waitKey(0);

    // Destroy window
    destroyAllWindows();

    return 0;
}

static void onChange(int pos, void* userInput)
{
    if (pos <= 0)
        return;
    Mat imgBlur;
    Mat* img = (Mat*)userInput;
    blur(*img, imgBlur, Size(pos, pos));
    imshow("Castle", imgBlur);
}

static void onMouse(int event, int x, int y, int, void* userInput)
{
    if (event != EVENT_LBUTTONDOWN)
        return;
    Mat* img = (Mat*)userInput;
    circle(*img, Point(x, y), 10, Scalar(0, 255, 0), 3);
    onChange(blurAmount, img);
}