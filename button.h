#ifndef CBUTTON_H
#define CBUTTON_H

#include <iostream>
#include <string>
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

using namespace std;

class CButton
{
public:
    static CButton* getInstance();
private:
    static CButton *instance;

    CButton();
    ~CButton();
    static void ISR(int signal);
    void initSignal();
};

#endif
