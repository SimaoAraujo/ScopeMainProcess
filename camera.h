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
    static CCamera* getInstance();
    static void* tAcquireImage(void*);
private:
    static CCamera *instance;
    VideoCapture videoCapture;

    CCamera();
    ~CCamera();
    void config(void);
    bool open(int);
    void close(void);
    bool isOpened(void);
    bool capture(int);
    void saveFrame(void);
};

#endif
