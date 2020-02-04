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
    static CRecord* getInstance();
    void createRecord();
    void create();
    CImage* getCImage();
    CText* getCText();
    CAudio* getCAudio();
    int getRecord();
private:
    static CImage *oImage;
    static CText *oText;
    static CAudio *oAudio;
    static int recordCount;
    static CRecord *instance;
    CRecord();
    ~CRecord();
};

#endif
