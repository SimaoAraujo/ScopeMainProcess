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
    system("/etc/init.d/initOS.sh");

    CImage *newImage = new CImage();
    CCamera oCamera(0, newImage);

    if(oCamera.captureFrame())
    {
        cout << "Image Captured and Saved!" << endl;
    }
    else
    {
        cout << "Error!" << endl;
    }

//    CScope* oScope = CScope::getInstance();

//    oScope->initMigSensors();
//    oScope->initSemaphores();
//    oScope->initMutexs();
//    oScope->initSignal();
//    oScope->fRun(); //only use the first letter in tasks of daemon functions???

//    pthread_exit(NULL);
}
