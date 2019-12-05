/*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.* SCOPE *.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*\
 *                                                                                                       *
 *                              Realized by Samuel Pereira and Simão Araújo                              *
 *                                                                                                       *
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
#include <vector>

using namespace std;

pthread_t tAcquireImageID, tDetectCharacterID, tRecognizeCharacterID,
    tAssembleTextID, tGenerateAudioID, tAdjustVolumeID, tIdleID;
sem_t semAcquireImage, semIncreaseVolume, semDecreaseVolume, semInterpretCharacter;
sem_t *semAccessAudio;
pthread_mutex_t mutexCamera, mutexImage, mutexFrame, mutexCharacters, mutexText, mutexAudio,
    mutexIncrease, mutexDecrease, mutexAcquireDetect, mutexRecognizeAssemble,
    mutexAssembleGenerate;

#endif
