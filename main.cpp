/*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.* SCOPE *.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*\
 *                                                                                                       *
 *                              Realized by Samuel Pereira and Simão Araújo                              *
 *                                                                                                       *
 *                                           Project Features:                                           *
 *                                                                                                       *
 *                    Produce sound based on patterns that are made in a touch matrix                    *
 *                                  React to some hands slide gestures                                   *
 *                Show a pattern in a matrix of leds, created by the user in touch inputs                *
 *                                   Detect pattern from touch matrix                                    *
 *                      Create a musical effect according with the matrix pattern                        *
 *                                            Produce melody                                             *
 *                                                                                                       *
\*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*/

#include "main.h"

int getDaemonPid()
{
    FILE *fp;
    char cmdInfo[10] = {};
    char cPid[10] = {};

    /* Open the command for reading. */
    fp = popen("ps -Af | grep /etc/Scope/ScopeDaemonProcess", "r");
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
    cout << "PID: "<< pid << endl;
    return pid;
}

void sendDaemonSignal()
{
    string signal = "kill -s SIGHUP " + to_string(getDaemonPid());
    system(signal.c_str());
}

struct buttonState
{
    char startButton;
    char increaseVolumeButton;
    char decreaseVolumeButton;
};

buttonState getButtonsState()
{
    char buttonsState[3] = {1, 1, 1};
    struct buttonState bs = {1, 1, 1};
    FILE* buttonsDeviceDriver;

    buttonsDeviceDriver = fopen ("/dev/buttons", "r");
    if(buttonsDeviceDriver != nullptr)
    {
        fread(buttonsState, sizeof(int), 3, buttonsDeviceDriver);
        fclose (buttonsDeviceDriver);

        cout << "buttonsState = " << buttonsState << endl;
        bs = {buttonsState[0], buttonsState[1], buttonsState[2]};
        return bs;
    }
    else
    {
        cout << "ERROR: can't open device." << endl;
        return bs;
    }
}

void generateAudio(string inputName, string outputName)
{
    string mimic = "mimic --setf duration_strech=2 /etc/Scope/record0/" /*+ to_string(recordCount) + "/"*/ + inputName + ".txt -voice ap -o /etc/Scope/record0/" + outputName + ".wav";
    system(mimic.c_str());

    cout << "generateAudio()" << endl;
}

int main()
{
    struct buttonState bs = {1, 1, 1};
    CScope *Scope = CScope::getInstance();

    string inputName = "helloText";
    string outputName = "helloText";
    generateAudio(inputName, outputName);

    inputName = "decodedText";
    outputName = "decodedText";
    generateAudio(inputName, outputName);

    sendDaemonSignal();

    bs = getButtonsState();

    if(bs.increaseVolumeButton == '0')
    {
        string amixerIncreseVolume = "amixer -c 0 set PCM 10db+";
        system(amixerIncreseVolume.c_str());
    }

    if(bs.decreaseVolumeButton == '0')
    {
        string amixerDecreaseVolume = "amixer -c 0 set PCM 10db-";
        system(amixerDecreaseVolume.c_str());
    }

    if(bs.startButton == '0')
    {
        if(!Scope->run())
            cout << "ERROR: Threads unable to execute." << endl;

        pthread_exit(nullptr);
    }

    return 0;
}
