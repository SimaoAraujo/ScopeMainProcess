#include "process.h"

CProcess* CProcess::instance = nullptr;

CProcess* CProcess::getInstance()
{
    if(!instance)
        instance = new CProcess();
    return instance;
}

CProcess::CProcess()
{

}

CProcess::~CProcess()
{

}

CRecord* CProcess::getCRecord()
{
    static CRecord *oRecord = CRecord::getInstance();
    oRecords.push_back(oRecord);
    return oRecord;
}

int CProcess::getDaemonPid()
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

void CProcess::sendDaemonSignal(string sig)
{
    string signal = "kill -s " + sig + " " + to_string(getDaemonPid());
    system(signal.c_str());
}
