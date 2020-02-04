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
sem_t semIncreaseVolume, semDecreaseVolume;
pthread_cond_t condAcquireImage, condAssembleText, condGenerateAudio;
pthread_mutex_t mutexAcquireImage, mutexAssembleText, mutexGenerateAudio;
pthread_mutex_t mutexCamera, mutexText, mutexAudio, mutexIncrease, mutexDecrease;
bool busy = false;
pthread_mutex_t mutexBusy;

#endif
