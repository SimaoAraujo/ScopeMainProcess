#ifndef CSCOPE_H
#define CSCOPE_H

#include <pthread.h>
#include <semaphore.h>
#include <signal.h>

#include <unistd.h> //sleep
#include <errno.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/fcntl.h>

#include <iostream>
#include <string>
#include "process.h"
#include "button.h"
#include "camera.h"
#include "earphone.h"

using namespace std;

class CScope
{
public:
    CScope();
    ~CScope();
    void config();
    void run();
private:
    CProcess oProcess;
    CButton oButtons;
    CCamera oCamera;
    CEarphone oEarphone;

    void initSemaphores();
    void initMutexes();
    void initConditionVariables();
    void initSignal();
    void configThread(uint8_t, pthread_attr_t *, struct sched_param *);
    int initThreads();
    static void ISR(int);
};

#endif // CSCOPE_H
