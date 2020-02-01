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
    bool capture(int);
private:
    static CCamera *instance;
    vector<CImage*> oImages;
    static VideoCapture* videoCapture;

    CCamera();
    ~CCamera();
    void config(void);
    void killProcess();
    int getCameraPid();
};

#endif
