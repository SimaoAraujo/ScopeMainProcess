#include "audio.h"

CAudio* CAudio::instance = nullptr;

CAudio* CAudio::getInstance(int recordCount)
{
    if(!instance)
        instance = new CAudio(recordCount);
    return instance;
}

int CAudio::recordCount = 0;

CAudio::CAudio(int recordCount)
{
    CAudio::recordCount = recordCount;
}

void CAudio::generate(string inputName, string outputName)
{
    string mimic = "mimic --setf duration_strech=2 /etc/SCOPE/record0/" /*+ to_string(recordCount) + "/"*/ + inputName + ".txt -voice ap -o /etc/SCOPE/record0/" + outputName + ".wav";
    system(mimic.c_str());

    cout << "CAudio::generate()" << endl;
}

int CAudio::getDaemonPid()
{
    FILE *fp;
    char cmdInfo[10] = {};
    char cPid[10] = {};

    /* Open the command for reading. */
    fp = popen("ps -Af | grep /etc/SCOPE/ScopeDaemonProcess", "r");
    if (fp == nullptr)
    {
        printf("Failed to run command\n" );
        exit(1);
    }

    /* Read the output a line at a time - output it. */
    fgets(cmdInfo, sizeof(cmdInfo), fp);

    /* close */
    pclose(fp);

    cout << cmdInfo << endl;

    int firstPidIndex = 0;
    while (cmdInfo[firstPidIndex] == ' ')
    {
        firstPidIndex++;
    }
    cout << firstPidIndex << endl;

    int cPidIndex = 0;
    while (cmdInfo[firstPidIndex] != ' ')
    {
        cPid[cPidIndex] = cmdInfo[firstPidIndex];
        cout << "cPid: " << cPid[cPidIndex] << endl;
        cPidIndex++;
        firstPidIndex++;
    }
    int pid = 0;
    pid = atoi(cPid);
    cout << "Daemon PID: "<< pid << endl;
    return pid;
}

void CAudio::sendDaemonSignal(string sig)
{
    string signal = "kill -s " + sig + " " + to_string(getDaemonPid());
    system(signal.c_str());
}

void* CAudio::tGenerateAudio(void *ptr)
{
    //extern sem_t *semAccessAudio;
    extern sem_t semBusy;
    extern pthread_cond_t condGenerateAudio;
    extern pthread_mutex_t mutexGenerateAudio, mutexAudio;

    while(1)
    {
        pthread_cond_wait(&condGenerateAudio, &mutexGenerateAudio);

        printf("audio\n");
        pthread_mutex_lock(&mutexAudio);
        CAudio::getInstance(0)->generate("text", "audio");
        CAudio::getInstance(0)->sendDaemonSignal("SIGHUP");
        pthread_mutex_unlock(&mutexAudio);

        sem_post(&semBusy);
    }
}
