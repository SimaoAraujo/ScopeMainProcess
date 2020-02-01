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
    static void* tIncreaseVolume(void*);
    static void* tDecreaseVolume(void*);
private:
    static CEarphone *instance;

    CEarphone();
    ~CEarphone();
};

#endif
