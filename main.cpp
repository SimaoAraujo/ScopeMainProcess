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


#include <iostream>

#include "scope.h"

using namespace std;

int main()
{
    CScope* oScope = CScope::getInstance();

    oScope->initMigSensors();
    oScope->initSemaphores();
    oScope->initMutexs();
    oScope->initSignal();
    oScope->fRun(); //only use the first letter in tasks of daemon functions???

    pthread_exit(NULL);
}
