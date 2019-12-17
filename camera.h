#ifndef CCAMERA_H
#define CCAMERA_H

#include <iostream>
#include <string>
#include <opencv2/opencv.hpp>
#include "image.h"
#include "record.h"

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
    vector<CImage*> oImages;

    CCamera();
    ~CCamera();
    void config(void);
    bool capture(int);
};

#endif
