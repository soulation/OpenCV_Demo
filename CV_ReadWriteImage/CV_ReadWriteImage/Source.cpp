#include <iostream>
#include <sstream>
#include <string>
using namespace std;

// OpenCV includes
#include "opencv2/core.hpp"
#include "opencv2/highgui.hpp"
using namespace cv;

int main(int argc, const char** argv)
{
    string imgPath = "castle.jpg";
    Mat normal = imread(imgPath);
    Mat reduceColor = imread(imgPath, IMREAD_REDUCED_COLOR_4);

    imwrite("castleReduce.jpg", reduceColor);

    imshow("Castle BGR", normal);
    imshow("Castle reduce color", reduceColor);

    // Wait for user to press a key.
    waitKey(0);
    return 0;
}
