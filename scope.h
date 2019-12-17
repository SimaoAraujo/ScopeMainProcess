#ifndef CSCOPE_H
#define CSCOPE_H

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
#include "process.h"
#include "button.h"
#include "camera.h"
#include "earphone.h"

using namespace std;

class CScope
{
public:
    static CScope* getInstance();
    bool run();
private:
    static CScope *instance;

    CScope();
    ~CScope();
    void initSemaphores();
    void initMutexes();
    void initConditionVariables();
    void initSignal();
    void initSharedMemory();
    static void *tIdle(void*);
    void setupThread(int, pthread_attr_t *, struct sched_param *);
    bool initThreads();
};

#endif
