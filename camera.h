#ifndef CCAMERA_H
#define CCAMERA_H

#include <iostream>
#include <string>
#include <opencv2/opencv.hpp>
#include "image.h"

using namespace std;
using namespace cv;

class CCamera
{
public:
    CCamera();
    CImage fTakeImage();
private:
    CImage oImage;
};

#endif // CCAMERA_H
