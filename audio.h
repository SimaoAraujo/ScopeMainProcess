#ifndef CAUDIO_H
#define CAUDIO_H

#include <iostream>
#include <string>

using namespace std;

class CAudio
{
public:
    CAudio();
    ~CAudio();
    static void *tGenerateAudio(void*);
private:
    string generateSound();
};

#endif
