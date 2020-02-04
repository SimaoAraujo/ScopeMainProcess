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
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

class CAudio
{
public:
    static CAudio* getInstance();
    static void* tGenerateAudio(void*);
    void sendDaemonSignal(string sig);
private:
    static CAudio *instance;
    static int recordCount;
    CAudio();
    ~CAudio();
    void generate(string, string);
    int getDaemonPid();
    int getRecord();
    void updateRecord();
};

#endif
