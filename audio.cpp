#include "audio.h"

CAudio* CAudio::instance = nullptr;

CAudio* CAudio::getInstance()
{
    if(!instance)
        instance = new CAudio();
    return instance;
}

int CAudio::recordCount = 0;

CAudio::CAudio()
{

}

int CAudio::getRecord()
{
    string sLastRecordCount;
    int iLastRecordCount;

    ifstream lastRecord_in("/etc/SCOPE/lastRecord.txt");
    if(lastRecord_in.is_open())
    {
        getline(lastRecord_in, sLastRecordCount);
        lastRecord_in.close();
        iLastRecordCount = stoi(sLastRecordCount);
        recordCount = iLastRecordCount;
        return recordCount;
    }
    else
    {
        cout << "Unable to open file";
    }
}

void CAudio::updateRecord()
{
    recordCount++;
    string sLastRecordCount = to_string(recordCount);

    ofstream lastRecord_out("/etc/SCOPE/lastRecord.txt", ofstream::out | ofstream::trunc);
    if(lastRecord_out.is_open())
    {
        lastRecord_out << sLastRecordCount;
        lastRecord_out.close();
    }
    else
    {
        cout << "Unable to open file";
    }
}

void CAudio::generate(string inputName, string outputName)
{
    getRecord();
    string mimic = "mimic --setf duration_strech=2 /etc/SCOPE/records/record" + to_string(recordCount) + "/" + inputName + ".txt -voice ap -o /etc/SCOPE/records/record" + to_string(recordCount) + "/" + outputName + ".wav";
    system(mimic.c_str());

    updateRecord();
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

    int cPidIndex = 0;
    while (cmdInfo[firstPidIndex] != ' ')
    {
        cPid[cPidIndex] = cmdInfo[firstPidIndex];
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
    extern sem_t semBusy;
    extern pthread_cond_t condGenerateAudio;
    extern pthread_mutex_t mutexGenerateAudio, mutexAudio;
    extern bool busy;
    extern pthread_mutex_t mutexBusy;

    while(1)
    {
        pthread_mutex_lock(&mutexGenerateAudio);
        pthread_cond_wait(&condGenerateAudio, &mutexGenerateAudio);
        pthread_mutex_unlock(&mutexGenerateAudio);

        pthread_mutex_lock(&mutexAudio);
        CAudio::getInstance()->generate("text", "audio");
        CAudio::getInstance()->sendDaemonSignal("SIGHUP");
        pthread_mutex_unlock(&mutexAudio);

        pthread_mutex_lock(&mutexBusy);
        busy = false;
        pthread_mutex_unlock(&mutexBusy);
    }
}
