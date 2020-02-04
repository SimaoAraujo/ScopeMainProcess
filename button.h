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
#include "record.h"
#include "process.h"

using namespace std;

class CButton
{
private:
    static CButton *instance;
    struct buttonState
    {
        char startButton;
        char increaseVolumeButton;
        char decreaseVolumeButton;
    };
    buttonState bs;
    CButton();
    ~CButton();
    buttonState getButtonsState();
    static void ISR(int signal);
public:
    static CButton* getInstance();
    void initSignal();
};

#endif
