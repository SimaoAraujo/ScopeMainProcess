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
    CImage();
    CImage(Mat*);
    ~CImage();
    void newInstance(Mat&);
    void saveNewInstance();
    static void *tAcquireImage(void*);
    static void *tDetectCharacter(void*);
    static void *tRecognizeCharacter(void*);
private:
    Mat image;
};

#endif
