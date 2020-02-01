#include "scope.h"

CScope* CScope::instance = nullptr;

CScope* CScope::getInstance()
{
    if(!instance)
        instance = new CScope();
    return instance;
}

CScope::CScope()
{
    initSemaphores();
    initMutexes();
    initConditionVariables();
    //initSharedMemory();

    system("/etc/SCOPE/ScopeDaemonProcess");
    CButton::getInstance()->initSignal();
}

CScope::~CScope()
{
    extern sem_t semAcquireImage, semAssembleText, semIncreaseVolume, semDecreaseVolume, semGenerateAudio, semBusy;
    //extern sem_t *semAccessAudio;
    extern pthread_cond_t condAssembleText, condGenerateAudio;
    extern pthread_mutex_t mutexCamera, mutexText, mutexAudio, mutexIncrease, mutexDecrease;

    sem_destroy(&semAcquireImage);
    sem_destroy(&semIncreaseVolume);
    sem_destroy(&semDecreaseVolume);
    sem_destroy(&semBusy);
//    sem_destroy(&semAssembleText);
//    sem_destroy(&semGenerateAudio);
//    sem_destroy(semAccessAudio);
    pthread_mutex_destroy(&mutexCamera);
    pthread_mutex_destroy(&mutexText);
    pthread_mutex_destroy(&mutexAudio);
//    pthread_mutex_destroy(&mutexIncrease);
//    pthread_mutex_destroy(&mutexDecrease);
    pthread_cond_destroy(&condAssembleText);
    pthread_cond_destroy(&condGenerateAudio);
}

void CScope::initSemaphores()
{
    extern sem_t semAcquireImage, semIncreaseVolume, semDecreaseVolume, semAssembleText, semGenerateAudio, semBusy;

    sem_init(&semAcquireImage, 0, 0);
    sem_init(&semIncreaseVolume, 0, 0);
    sem_init(&semDecreaseVolume, 0, 0);
    sem_init(&semBusy, 0, 1);
//    sem_init(&semAssembleText, 0 , 0);
//    sem_init(&semGenerateAudio, 0 , 0);
}

void CScope::initMutexes()
{
    extern pthread_mutex_t mutexCamera, mutexText, mutexAudio, mutexIncrease, mutexDecrease;

    mutexCamera = PTHREAD_MUTEX_INITIALIZER;
    mutexText = PTHREAD_MUTEX_INITIALIZER;
    mutexAudio = PTHREAD_MUTEX_INITIALIZER;
    mutexIncrease = PTHREAD_MUTEX_INITIALIZER;
    mutexDecrease = PTHREAD_MUTEX_INITIALIZER;
}

void CScope::initConditionVariables()
{
    extern pthread_cond_t condAssembleText, condGenerateAudio;
    extern pthread_mutex_t mutexAssembleText, mutexGenerateAudio;

    condAssembleText = PTHREAD_COND_INITIALIZER;
    mutexAssembleText = PTHREAD_MUTEX_INITIALIZER;
    condGenerateAudio = PTHREAD_COND_INITIALIZER;
    mutexGenerateAudio = PTHREAD_MUTEX_INITIALIZER;
}

void CScope::initSharedMemory()
{
//    extern sem_t *semAccessAudio;

//    char shmName[] = "shmDaemon";
//    char semName[] = "semDaemon";

//    shm_open(shmName, O_CREAT|O_RDWR|O_TRUNC, S_IRWXU|S_IRWXG);
//    semAccessAudio = sem_open(semName, O_CREAT, 0644, 0);
//    sem_close(semAccessAudio);
}

void CScope::setupThread(int priority, pthread_attr_t *pthread_attr, sched_param *pthread_param)
{
    pthread_attr_setschedpolicy (pthread_attr, SCHED_RR);
    pthread_param->sched_priority = priority;
    pthread_attr_setschedparam (pthread_attr, pthread_param);
    pthread_attr_setinheritsched (pthread_attr, PTHREAD_EXPLICIT_SCHED);
}

bool CScope::initThreads()
{
    extern pthread_t tAcquireImageID, tAssembleTextID, tGenerateAudioID, tIncreaseVolumeID, tDecreaseVolumeID;
    int tAcquireImageRET, tAssembleTextRET, tGenerateAudioRET, tIncreaseVolumeRET, tDecreaseVolumeRET;
    int threadPolicy;
    pthread_attr_t threadAttr;
    struct sched_param threadParam;

    static CProcess *oProcess = CProcess::getInstance();
    static CCamera *oCamera = CCamera::getInstance();
    static CEarphone *oEarphone = CEarphone::getInstance();

    pthread_attr_init(&threadAttr);
    pthread_attr_getschedparam(&threadAttr, &threadParam);
    pthread_attr_getschedpolicy(&threadAttr, &threadPolicy);

    setupThread(5, &threadAttr, &threadParam);
    tAcquireImageRET = pthread_create(&tAcquireImageID, &threadAttr, oCamera->tAcquireImage, nullptr);

    setupThread(4, &threadAttr, &threadParam);
    tAssembleTextRET = pthread_create(&tAssembleTextID, &threadAttr, oProcess->getCRecord()->getCText()->tAssembleText, nullptr);

    setupThread(3, &threadAttr, &threadParam);
    tGenerateAudioRET = pthread_create(&tGenerateAudioID, &threadAttr, oProcess->getCRecord()->getCAudio()->tGenerateAudio, nullptr);

    setupThread(1, &threadAttr, &threadParam);
    tIncreaseVolumeRET = pthread_create(&tIncreaseVolumeID, &threadAttr, oEarphone->tIncreaseVolume, nullptr);

    setupThread(2, &threadAttr, &threadParam);
    tDecreaseVolumeRET = pthread_create(&tDecreaseVolumeID, &threadAttr, oEarphone->tDecreaseVolume, nullptr);

    /* pthread_create returns 0 if successful! */
    if((tAcquireImageRET != 0)&&(tAssembleTextRET != 0)&&(tGenerateAudioRET != 0)&&(tIncreaseVolumeRET != 0)&&(tDecreaseVolumeRET != 0))
    {
        perror("ERROR: Failed Creating Thread.");
        return 0;
    }
    else
        return 1;
}

bool CScope::run()
{
    extern pthread_t tAcquireImageID, tAssembleTextID, tGenerateAudioID, tIncreaseVolumeID, tDecreaseVolumeID;

    if(initThreads())
    {
        pthread_join(tIncreaseVolumeID, nullptr);
        pthread_join(tDecreaseVolumeID, nullptr);
        pthread_join(tAssembleTextID, nullptr);
        pthread_join(tGenerateAudioID, nullptr);
        pthread_join(tAcquireImageID, nullptr);

        return 1;
    }
    else
        return 0;
}
