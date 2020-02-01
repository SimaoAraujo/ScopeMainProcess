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
#include "audio.h"
#include "camera.h"
#include <vector>

using namespace std;

pthread_t tAcquireImageID, tAssembleTextID, tGenerateAudioID, tIncreaseVolumeID, tDecreaseVolumeID;
sem_t semAcquireImage, semIncreaseVolume, semDecreaseVolume, semAssembleText, semGenerateAudio, semBusy;
//sem_t *semAccessAudio;
pthread_cond_t condAssembleText, condGenerateAudio;
pthread_mutex_t mutexAssembleText, mutexGenerateAudio;
pthread_mutex_t mutexCamera, mutexText, mutexAudio, mutexIncrease, mutexDecrease;

#endif
