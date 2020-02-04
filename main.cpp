/*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.* SCOPE *.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*\
 *                                                                                                       *
 *                                  Made by Samuel Pereira and Simão Araújo                              *
 *                                                                                                       *
 *                                           Project Features:                                           *
 *                                                                                                       *
 *                                Capture images from a camera and save it                               *
 *                                    Detect Text in the images taken                                    *
 *                                Recognize the detected text and save it                                *
 *                                 Convert the recognized text into audio                                *
 *                     Reproduce the audio converted from the text detected in the image                 *
 *                                          Adjust the sound level                                       *
 *                                                                                                       *
\*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*/

#include "main.h"

int main()
{
    CScope *Scope = CScope::getInstance();

    if(!Scope->run())
        cout << "ERROR: Threads unable to execute." << endl;

    pthread_exit(nullptr);
}
