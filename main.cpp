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
    CScope *Scope = CScope::getInstance();

    if(!Scope->run())
        cout << "ERROR: Threads unable to execute." << endl;

    pthread_exit(nullptr);

//    CCamera::getInstance()->capture(0);
//    CText::getInstance(0)->assembleText();
//    generateAudio("text", "audio");
//    sendDaemonSignal();
}
