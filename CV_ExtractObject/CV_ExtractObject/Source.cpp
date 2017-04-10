#include <iostream>
#include <string>
#include "opencv2/core.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
using namespace cv;

int main(int argc, const char** argv)
{
    Mat object;
    Mat background, background;
    Mat difference;
    Mat division;

    String path = "../../Resource/";
    object = imread(path + "object.jpg", IMREAD_REDUCED_COLOR_4);
    background = imread(path + "background.jpg", IMREAD_REDUCED_COLOR_4);
    difference = background - object;
    division = (1 - (object / background)) * 255;

    imshow("Object", object);
    imshow("Background", background);
    imshow("Background - Object", difference);
    imshow("Object / Background", division);


    waitKey();
}