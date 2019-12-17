#ifndef CAUDIO_H
#define CAUDIO_H

#include <pthread.h>
#include <semaphore.h>
#include <signal.h>
#include <unistd.h> //sleep
#include <errno.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/fcntl.h>
#include <iostream>
#include <string>

using namespace std;

class CAudio
{
public:
    static CAudio* getInstance(int);
    static void* tGenerateAudio(void*);
private:
    static CAudio *instance;
    static int recordCount;

    CAudio(int);
    ~CAudio();
    string generateSound();
    void generate(string, string);
};

#endif
