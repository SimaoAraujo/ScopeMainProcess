#ifndef CEARPHONE_H
#define CEARPHONE_H

#include <iostream>
#include <string>
#include "audio.h"

using namespace std;

class CEarphone
{
public:
    static CEarphone* getInstance();
    static void* tAdjustVolume(void*);
private:
    static CEarphone *instance;
    //CAudio oAudio;

    CEarphone();
    ~CEarphone();
};

#endif
