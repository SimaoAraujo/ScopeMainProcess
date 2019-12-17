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
    string mimic = "mimic --setf duration_strech=1.2 /etc/Scope/record0/" /*+ to_string(recordCount) + "/"*/ + inputName + ".txt -voice ap -o /etc/Scope/record0/" + outputName + ".wav";
    cout << "CAudio::generate()" << endl;
    system(mimic.c_str());

    cout << "CAudio::generate()" << endl;
}

void* CAudio::tGenerateAudio(void *ptr)
{
    extern sem_t semUpdateSound, *semAccessAudio, semGenerateAudio;
    extern pthread_mutex_t mutexAudio;

    string inputName = "helloText";
    string outputName = "helloText";
    string mimic = "mimic --setf duration_strech=2 /etc/Scope/record0/" /*+ to_string(recordCount) + "/"*/ + inputName + ".txt -voice ap -o /etc/Scope/record0/" + outputName + ".wav";
    cout << "CAudio::generate()" << endl;


        //sem_wait(&semGenerateAudio);
        pthread_mutex_lock(&mutexAudio);
        system(mimic.c_str());
        pthread_mutex_unlock(&mutexAudio);
        cout << "CAudio::generate()" << endl;

        inputName = "decodedText";
        outputName = "decodedText";
        mimic = "mimic --setf duration_strech=1.2 /etc/Scope/record0/" /*+ to_string(recordCount) + "/"*/ + inputName + ".txt -voice ap -o /etc/Scope/record0/" + outputName + ".wav";
        cout << "CAudio::generate()" << endl;
        pthread_mutex_lock(&mutexAudio);
        system(mimic.c_str());
        pthread_mutex_unlock(&mutexAudio);
        cout << "CAudio::generate()" << endl;


        FILE *fp;
        char path[10];
        char aux[10];

        /* Open the command for reading. */
        fp = popen("ps -Af | grep /root/ScopeDaemonProcess", "r");
        if (fp == nullptr)
        {
            printf("Failed to run command\n" );
            exit(1);
        }

        /* Read the output a line at a time - output it. */
        fgets(path, sizeof(path), fp);

        /* close */
        pclose(fp);

        int i = 0;
        while (path[++i] != ' ')
        {
            aux[i - 1] = path[i];
            cout << path[i] << endl;
        }
        int pid = atoi(aux);
        cout << pid << endl;


        string signal = "kill -s SIGHUP " + to_string(pid);
        system(signal.c_str());

    //    CAudio::getInstance(0)->generate("decodedText", "decodedText");
    //    CAudio::getInstance(0)->generate("helloText", "helloText");


    pthread_exit(nullptr);
}
