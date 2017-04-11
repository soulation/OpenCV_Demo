#include <iostream>
#include <string>
#include <vector>
using namespace std;
#include "opencv2/core.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
using namespace cv;

const struct card_feature {
    vector<Point> portrait;
    vector<Point> name;
    vector<Point> power;
    vector<Point> star;
    vector<Point> desc;

    // Constructor to fill up data.
    card_feature(double w, double h) 
    {
        name.push_back(Point(w*0.085, h*0.05172413793));
        name.push_back(Point(w*0.9125, h*0.13793103448));
        portrait.push_back(Point(50, 115));
        portrait.push_back(Point(350, 420));
        desc.push_back(Point(35, 440));
        desc.push_back(Point(365, 529));
        power.push_back(Point(35, 530));
        power.push_back(Point(365, 550));
    }
};

void extractFeature(const Mat input, Mat& output, int mode);
void drawCardFeatureRec(const Mat input, const card_feature f);
int main(int argc, const char** argv)
{
    Mat input = imread("../../Resource/skull.jpg", IMREAD_COLOR);
    card_feature feature(input.cols, input.rows);
    drawCardFeatureRec(input, feature);
    imshow("Dragon", input);
    waitKey();
}

void extractFeature(const Mat input, Mat& output, int mode)
{
    switch (mode)
    {
        case 0:

            break;
        case 1:
            break;
        default:
            break;
    }
}

void drawCardFeatureRec(const Mat input, const card_feature f)
{
    rectangle(input, f.name[0], f.name[1], Scalar(0,0,255), 0, LINE_8, 0);
    rectangle(input, f.portrait[0], f.portrait[1], Scalar(255,0,0), 0, LINE_8, 0);
    rectangle(input, f.desc[0], f.desc[1], Scalar(0, 255, 0), 0, LINE_8, 0);
    rectangle(input, f.power[0], f.power[1], Scalar(0, 0, 255), 0, LINE_8, 0);
}