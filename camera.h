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
    CCamera(int, CImage*);
    ~CCamera();
    void config(void);
    bool open(void);
    void close(void);
    bool isOpened(void);
    bool captureFrame(void);
    void saveFrame(void);
private:
    VideoCapture videoCapture;
    int cameraId;
    CImage *pImage;
};

#endif // CCAMERA_H
