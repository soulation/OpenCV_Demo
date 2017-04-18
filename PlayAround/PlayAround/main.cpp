#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>

using namespace cv;

void onMouseCallback(int event, int x, int y, int flags, void* param);

int main(void)
{
    Mat img = imread("../../Resource/castle.jpg");
    imshow("Output", img);
    setMouseCallback("Output", onMouseCallback, reinterpret_cast<void*>(&img));
    waitKey();

}

void onMouseCallback(int event, int x, int y, int flags, void* param)
{
    Mat *img = reinterpret_cast<Mat*>(param);
    switch (event)
    {
        case EVENT_LBUTTONDOWN:
            flip(*img, *img, 1);
            imshow("Output", *img);
            break;
    }

}