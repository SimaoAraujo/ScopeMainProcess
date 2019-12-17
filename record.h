#ifndef CRECORD_H
#define CRECORD_H

#include <iostream>
#include <string>
#include "image.h"
#include "text.h"
#include "audio.h"

using namespace std;

class CRecord
{
public:
    CRecord();
    ~CRecord();
    int create();
    CImage* getCImage();
    CText* getCText();
    CAudio* getCAudio();
private:
    static CImage *oImage;
    static CText *oText;
    static CAudio *oAudio;
    static int recordCount;
};

#endif
