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

int main()
{
    string inputName = "helloText";
    string outputName = "helloText";

    string mimic = "mimic --setf duration_strech=2 /etc/Scope/record0/" /*+ to_string(recordCount) + "/"*/ + inputName + ".txt -voice ap -o /etc/Scope/record0/" + outputName + ".wav";
    cout << "CAudio::generate()" << endl;
    system(mimic.c_str());

    cout << "CAudio::generate()" << endl;

    inputName = "decodedText";
    outputName = "decodedText";

    mimic = "mimic --setf duration_strech=1.2 /etc/Scope/record0/" /*+ to_string(recordCount) + "/"*/ + inputName + ".txt -voice ap -o /etc/Scope/record0/" + outputName + ".wav";
    cout << "CAudio::generate()" << endl;
    system(mimic.c_str());

    cout << "CAudio::generate()" << endl;

    CScope *Scope = CScope::getInstance();


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

    int i = -1;
    while (path[++i] != ' ')
    {
        aux[i] = path[i];
        cout << path[i] << endl;
    }
    int pid = atoi(aux);
    cout << pid << endl;


    string signal = "kill -s SIGHUP " + to_string(pid);
    system(signal.c_str());


    char buffer[3]={0};
    FILE* fd ;
    fd = fopen ("/dev/buttons", "r" );
    if(fd == nullptr)
    {
        printf ("Device doesn't exist\n");
        return -1;
    }
    fread(buffer, sizeof(int), 3, fd);
    printf ("Values on buffer: %s\n", buffer);
    printf ("Values on buffer: %d\n", atoi(buffer));
    fclose (fd);

    if(buffer[0] == '0')
    {
        cout << "button pressed!" << endl;
    }
    else
        cout << "no button pressed!!!!!!!11" << endl;

    if(!Scope->run())
        cout << "ERROR: Threads unable to execute." << endl;

    pthread_exit(nullptr);
}
