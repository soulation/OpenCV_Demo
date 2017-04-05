#include "opencv2/core/utility.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
using namespace cv;

int main(int argc, const char** argv)
{
    Mat castle = imread("castle.jpg");

    imshow("Castle", castle);

    waitKey(0);
    return 1;
}