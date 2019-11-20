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

#ifndef MAIN_H
#define MAIN_H

#include <iostream>
#include <string>
#include <mqueue.h>
#include <pthread.h>
#include <semaphore.h>
#include "scope.h"
#include "image.h"
#include "camera.h"

using namespace std;

/****************************Thread identifier*****************************/

pthread_t tAcquireImage;
pthread_t tDetectCharacter;
pthread_t tRecognizeCharacter;
pthread_t tAssembleText;
pthread_t tGenerateAudio;
pthread_t tAdjustVolume ;
pthread_t tIdle ;

/****************************Semaphore identifier**************************/

sem_t semAcquireImage;
sem_t semIncreaseVolume;
sem_t semDecreaseVolume;
sem_t semInterpretCharacter;
sem_t *semAccessAudio;

/****************************Mutex identifier******************************/

pthread_mutex_t mutexImage;
pthread_mutex_t mutexFrame;
pthread_mutex_t mutexCharacters;
pthread_mutex_t mutexText;
pthread_mutex_t mutexAudio;
pthread_mutex_t mutexIncrease;
pthread_mutex_t mutexDecrease;
pthread_mutex_t mutexAcquireDetect;
pthread_mutex_t mutexRecognizeAssemble;
pthread_mutex_t mutexAssembleGenerate;

#endif // MAIN_H
