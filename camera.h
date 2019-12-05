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

    void config(void);
    bool open(void);
    void close(void);
    bool isOpened(void);
    bool captureFrame(void);
    void saveFrame(void);
private:
    static CCamera *instance;

    VideoCapture videoCapture;
    int cameraId;
    CImage *pImage;

    /*********************CHECK CONSTRUCTOR************************/
    /* Not receiving arguments because of Singleton Class! */
    CCamera();
    CCamera(int, CImage*);
    ~CCamera();
};

#endif
