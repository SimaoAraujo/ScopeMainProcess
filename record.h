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
private:
    CImage      oImage;
    CText       oText;
    CAudio      oAudio;
};

#endif // CRECORD_H
