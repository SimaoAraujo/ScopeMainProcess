#include "earphone.h"

CEarphone* CEarphone::instance = nullptr;

CEarphone* CEarphone::getInstance()
{
    if(!instance)
        instance = new CEarphone();
    return instance;
}

CEarphone::CEarphone()
{

}

void* CEarphone::tIncreaseVolume(void *ptr)
{
    extern sem_t semIncreaseVolume;
    extern pthread_mutex_t mutexAudio;
    string amixerIncreseVolume = "amixer -c 0 set PCM 10db+";

    while (1)
    {
        sem_wait(&semIncreaseVolume);
        printf("increase\n");
        system(amixerIncreseVolume.c_str());
        CAudio::getInstance(0)->sendDaemonSignal("SIGUSR2");
    }
}

void* CEarphone::tDecreaseVolume(void *ptr)
{
    extern sem_t semDecreaseVolume;
    extern pthread_mutex_t mutexAudio;
    string amixerDecreaseVolume = "amixer -c 0 set PCM 10db-";

    while (1)
    {
        sem_wait(&semDecreaseVolume);
        printf("decrease\n");
        system(amixerDecreaseVolume.c_str());
        CAudio::getInstance(0)->sendDaemonSignal("SIGUSR2");
    }
}
