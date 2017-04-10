#include <iostream>
#include <string>
#include "opencv2/core.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include "wtypes.h"

using namespace cv;

Mat removeBackground(Mat object, Mat background);
void getDesktopResolution(int& horizontal, int& vertical);

int main(int argc, const char** argv)
{
    Mat object;
    Mat background, background32;
    Mat difference;
    Mat division;

    int screen_width;
    int screen_height;

    getDesktopResolution(screen_width, screen_height);

    String path = "../../Resource/";
    object = imread(path + "object.jpg", IMREAD_REDUCED_GRAYSCALE_4);
    background = imread(path + "background.jpg", IMREAD_REDUCED_GRAYSCALE_4);

    // Remove noise
    //medianBlur(object, object, 3);
    //medianBlur(background, background, 3);

    difference = removeBackground(object, background);
    //division = (1 - (object / background)) * 255;

    imshow("Object", object);
    imshow("Background", background);
    imshow("Background - Object", difference);

    // Position screens position
    moveWindow("Object", 80,0);
    moveWindow("Background", screen_width/4, screen_height/2);

    waitKey();
}

Mat removeBackground(Mat object, Mat background)
{
    return background - object;
}

void getDesktopResolution(int& horizontal, int& vertical)
{
    RECT desktop;
    const HWND hDesktop = GetDesktopWindow();
    GetWindowRect(hDesktop, &desktop);

    horizontal = desktop.right;
    vertical = desktop.bottom;
}