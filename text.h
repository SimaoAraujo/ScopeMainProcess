#ifndef CTEXT_H
#define CTEXT_H

#include <iostream>
#include <semaphore.h>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <opencv2/opencv.hpp>
#include <tesseract/baseapi.h>

using namespace std;
using namespace cv;
using namespace tesseract;

class CText
{
public:
    static CText* getInstance();
    static void* tAssembleText(void*);

private:
    static CText *instance;
    static int recordCount;
    CText();
    ~CText();
    void createFile(string, string);
    void assemble();
    int getRecord();
};

#endif
