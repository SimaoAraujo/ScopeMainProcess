#ifndef CIMAGE_H
#define CIMAGE_H

#include <iostream>
#include <string>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

class CImage
{
public:
    static CImage* getInstance(int);
    void save(Mat);
private:
    static CImage *instance;
    Mat image;
    static int recordCount;

    CImage(int);
    ~CImage();
};

#endif
