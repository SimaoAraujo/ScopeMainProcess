#include "earphone.h"

CEarphone* CEarphone::instance = nullptr;

CEarphone* CEarphone::getInstance()
{
    if(!instance)
        instance = new CEarphone();
    return instance;
}

CEarphone::CEarphone() : oAudio()
{

}

void *CEarphone::tAdjustVolume(void *ptr)
{
    while (1)
    {
        cout << "Arrived at: tAdjustVolume" << endl;
    }
}
