#include "scope.h"

CScope::CScope(): oProcess(), oButtons(), oCamera(), oEarphone()
{
    extern sem_t *semAccessAudio;

    char shmName[] = "shmDaemon";
    char semName[] = "semDaemon";

    shm_open(shmName, O_CREAT|O_RDWR|O_TRUNC, S_IRWXU|S_IRWXG);
    semAccessAudio = sem_open(semName, O_CREAT, 0644, 0);
    sem_close(semAccessAudio);

    system("/root/ScopeDaemonProcess");

}

CScope::~CScope()
{

}

void CScope::initSemaphores()
{
    extern sem_t semAcquireImage;
    extern sem_t semIncreaseVolume;
    extern sem_t semDecreaseVolume;
    extern sem_t semInterpretCharacter;

    sem_init (&semAcquireImage, 0, 0);
    sem_init (&semIncreaseVolume, 0, 0);
    sem_init (&semDecreaseVolume, 0, 0);
    sem_init (&semInterpretCharacter, 0 , 0);

    /*********************** WHY???? *******************/
    return;
}

void CScope::initMutexes()
{
    extern pthread_mutex_t mutexImage;
    extern pthread_mutex_t mutexFrame;
    extern pthread_mutex_t mutexCharacters;
    extern pthread_mutex_t mutexText;
    extern pthread_mutex_t mutexAudio;
    extern pthread_mutex_t mutexIncrease;
    extern pthread_mutex_t mutexDecrease;
    extern pthread_mutex_t mutexAcquireDetect;
    extern pthread_mutex_t mutexRecognizeAssemble;
    extern pthread_mutex_t mutexAssembleGenerate;

    mutexImage = PTHREAD_MUTEX_INITIALIZER;
    mutexFrame = PTHREAD_MUTEX_INITIALIZER;
    mutexCharacters = PTHREAD_MUTEX_INITIALIZER;
    mutexText = PTHREAD_MUTEX_INITIALIZER;
    mutexAudio = PTHREAD_MUTEX_INITIALIZER;
    mutexIncrease = PTHREAD_MUTEX_INITIALIZER;
    mutexDecrease = PTHREAD_MUTEX_INITIALIZER;
    mutexAcquireDetect = PTHREAD_MUTEX_INITIALIZER;
    mutexRecognizeAssemble = PTHREAD_MUTEX_INITIALIZER;
    mutexAssembleGenerate = PTHREAD_MUTEX_INITIALIZER;
}

void CScope::initSignal()
{
    struct itimerval itv;

    signal(SIGALRM, ISR);

    /* it_interval -> timer reload: 8ms */
    itv.it_interval.tv_sec = 0;
    itv.it_interval.tv_usec = 8000;
    /* it_value -> timer value: 8ms */
    itv.it_value.tv_sec = 0;
    itv.it_value.tv_usec = 8000;

    setitimer(ITIMER_REAL, &itv, NULL);	//ITIMER_REAL is for a SIGALRM

    /*********************** WHY???? *******************/
    return;
}

void CScope::ISR(int signal)
{
    extern sem_t semAcquireIMage;
    extern sem_t semIncreaseVolume;
    extern sem_t semDecreaseVolume;

    static int count = 0;
    if(signal == SIGALRM)
    {
        /* Post to the semaphore to sample the sensors */
        switch (++count)
        {
            case 1:
                sem_post(&semAcquireIMage);
                break;
            case 2:
                sem_post(&semIncreaseVolume);
                break;
            case 3:
                sem_post(&semDecreaseVolume);
                break;
            default:
                count = 0;
                break;
        }
    }
}

void CScope::configThread(uint8_t priority, pthread_attr_t *pthread_attr, sched_param *pthread_param)
{
    pthread_attr_setschedpolicy (pthread_attr, SCHED_RR);
    pthread_param->sched_priority = priority;
    pthread_attr_setschedparam (pthread_attr, pthread_param);
}

int CScope::initThreads()
{
    int error_tDetectCharacter, error_tRecognizeCharacter, error_tAssembleText, error_tGenerateAudio, error_tAdjustVolume, error_tIdle;
    extern pthread_t tDetectCharacter, tRecognizeCharacter, tAssembleText, tGenerateAudio, tAdjustVolume, tIdle;

    CTouchMatrix *touch = CTouchMatrix::getInstance();
    CHandSlideSensor *slideSensor = CHandSlideSensor::getInstance();
    CDistanceSensor *distanceSensor =  CDistanceSensor::getInstance();
    CGenerateSound generateSoundc;

    int threadPolicy;
    pthread_attr_t threadAttr;
    struct sched_param threadParam;

    pthread_attr_init(&threadAttr);
    pthread_attr_getschedparam(&threadAttr, &threadParam);
    pthread_attr_getschedpolicy(&threadAttr, &threadPolicy);

    /* define prioratie tTouch */
    configThread(1, &threadAttr, &threadParam);
    pthread_attr_setinheritsched (&threadAttr, PTHREAD_EXPLICIT_SCHED);
    error_tDetectCharacter = pthread_create(&tDetectCharacter, &threadAttr, touch->tTouchFunction, NULL);

    /* define prioratie tIRSensor */
    configThread(2, &threadAttr, &threadParam);
    pthread_attr_setinheritsched (&threadAttr, PTHREAD_EXPLICIT_SCHED);
    error_tRecognizeCharacter = pthread_create(&tRecognizeCharacter, &threadAttr, distanceSensor->tIRSensorFunction, NULL);

    /* define prioratie tSlideSensor */
    configThread(2, &threadAttr, &threadParam);
    pthread_attr_setinheritsched (&threadAttr, PTHREAD_EXPLICIT_SCHED);
    error_tAssembleText = pthread_create(&tAssembleText, &threadAttr, slideSensor->tSlideSensorFunction, NULL);

    /* define prioratie tSoundGenerater */
    configThread(3, &threadAttr, &threadParam);
    pthread_attr_setinheritsched (&threadAttr, PTHREAD_EXPLICIT_SCHED);
    error_tGenerateAudio = pthread_create(&tGenerateAudio, &threadAttr, generateSoundc.tSoundGeneraterFunction, NULL);

    /* define prioratie tSoundGenerater */
    configThread(3, &threadAttr, &threadParam);
    pthread_attr_setinheritsched (&threadAttr, PTHREAD_EXPLICIT_SCHED);
    error_tAdjustVolume = pthread_create(&tAdjustVolume, &threadAttr, generateSoundc.tSoundGeneraterFunction, NULL);

    /* define prioratie tSoundGenerater */
    configThread(3, &threadAttr, &threadParam);
    pthread_attr_setinheritsched (&threadAttr, PTHREAD_EXPLICIT_SCHED);
    error_tIdle = pthread_create(&tIdle,&threadAttr,generateSoundc.tSoundGeneraterFunction,NULL);

    if((error_tDetectCharacter != 0)&&(error_tRecognizeCharacter != 0)&&(error_tAssembleText != 0)&&(error_tGenerateAudio != 0)&&(error_tAdjustVolume != 0)&&(error_tIdle != 0))
    {
        perror("ERROR: Failed Creating Threads.");
        return -1;
    }

    return 0;
}
