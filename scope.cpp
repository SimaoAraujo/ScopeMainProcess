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
    CButton::getInstance();

    initSemaphores();
    initMutexes();
    initConditionVariables();
    initSharedMemory();
}

CScope::~CScope()
{
    extern sem_t semAcquireImage, semIncreaseVolume, semDecreaseVolume, semInterpretCharacter, semGenerateAudio;
    extern sem_t *semAccessAudio;
    extern pthread_mutex_t mutexImage, mutexFrame, mutexCharacters, mutexText, mutexAudio,
        mutexIncrease, mutexDecrease, mutexAcquireDetect, mutexRecognizeAssemble,
        mutexAssembleGenerate;

    sem_destroy(&semAcquireImage);
    sem_destroy(&semIncreaseVolume);
    sem_destroy(&semDecreaseVolume);
    sem_destroy(&semInterpretCharacter);
    sem_destroy(&semGenerateAudio);
    sem_destroy(semAccessAudio);
    pthread_mutex_destroy(&mutexImage);
    pthread_mutex_destroy(&mutexFrame);
    pthread_mutex_destroy(&mutexCharacters);
    pthread_mutex_destroy(&mutexText);
    pthread_mutex_destroy(&mutexAudio);
    pthread_mutex_destroy(&mutexIncrease);
    pthread_mutex_destroy(&mutexDecrease);
    pthread_mutex_destroy(&mutexAcquireDetect);
    pthread_mutex_destroy(&mutexRecognizeAssemble);
    pthread_mutex_destroy(&mutexAssembleGenerate);
//    pthread_cond_destroy(&cond_new_rfid);
}

void CScope::initSemaphores()
{
    extern sem_t semAcquireImage, semIncreaseVolume, semDecreaseVolume, semInterpretCharacter, semGenerateAudio;

    sem_init (&semAcquireImage, 0, 0);
    sem_init (&semIncreaseVolume, 0, 0);
    sem_init (&semDecreaseVolume, 0, 0);
    sem_init (&semInterpretCharacter, 0 , 0);
    sem_init (&semGenerateAudio, 0 , 0);
}

void CScope::initMutexes()
{
    extern pthread_mutex_t mutexImage, mutexFrame, mutexCharacters, mutexText, mutexAudio,
        mutexIncrease, mutexDecrease, mutexAcquireDetect, mutexRecognizeAssemble,
        mutexAssembleGenerate;

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

void CScope::initConditionVariables()
{

}

void CScope::initSharedMemory()
{
    extern sem_t *semAccessAudio;

    char shmName[] = "shmDaemon";
    char semName[] = "semDaemon";

    shm_open(shmName, O_CREAT|O_RDWR|O_TRUNC, S_IRWXU|S_IRWXG);
    semAccessAudio = sem_open(semName, O_CREAT, 0644, 0);
    sem_close(semAccessAudio);

    system("/etc/Scope/ScopeDaemonProcess");
}

void* CScope::tIdle(void *ptr)
{
    while (1)
    {
        cout << "Arrived at: tIdle" << endl;
    }
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
    extern pthread_t tAcquireImageID, tDetectCharacterID, tRecognizeCharacterID,
        tAssembleTextID, tGenerateAudioID, tAdjustVolumeID, tIdleID;
    int tAcquireImageRET, tDetectCharacterRET, tRecognizeCharacterRET, tAssembleTextRET,
        tGenerateAudioRET, tAdjustVolumeRET, tIdleRET;
    int threadPolicy;
    pthread_attr_t threadAttr;
    struct sched_param threadParam;

    static CProcess *oProcess = CProcess::getInstance();
    static CCamera *oCamera = CCamera::getInstance();
    //static CEarphone *oEarphone = CEarphone::getInstance();

    pthread_attr_init(&threadAttr);
    pthread_attr_getschedparam(&threadAttr, &threadParam);
    pthread_attr_getschedpolicy(&threadAttr, &threadPolicy);

    setupThread(1, &threadAttr, &threadParam);
    tAcquireImageRET = pthread_create(&tAcquireImageID, &threadAttr, oCamera->tAcquireImage, nullptr);

//    setupThread(3, &threadAttr, &threadParam);
//    tDetectCharacterRET = pthread_create(&tDetectCharacterID, &threadAttr, oProcess->getCRecord()->getCImage()->tDetectCharacter, nullptr);

//    setupThread(3, &threadAttr, &threadParam);
//    tRecognizeCharacterRET = pthread_create(&tRecognizeCharacterID, &threadAttr, oProcess->getCRecord()->getCImage()->tRecognizeCharacter, nullptr);

    setupThread(4, &threadAttr, &threadParam);
    tAssembleTextRET = pthread_create(&tAssembleTextID, &threadAttr, oProcess->getCRecord()->getCText()->tAssembleText, nullptr);

//    setupThread(2, &threadAttr, &threadParam);
//    tGenerateAudioRET = pthread_create(&tGenerateAudioID, &threadAttr, oProcess->getCRecord()->getCAudio()->tGenerateAudio, nullptr);

//    setupThread(1, &threadAttr, &threadParam);
//    tAdjustVolumeRET = pthread_create(&tAdjustVolumeID, &threadAttr, oEarphone->tAdjustVolume, nullptr);

//    setupThread(5, &threadAttr, &threadParam);
//    tIdleRET = pthread_create(&tIdleID, &threadAttr, this->tIdle, nullptr);

    /* pthread_create returns 0 if successful! */
    if((tAcquireImageRET != 0)&&(tDetectCharacterRET != 0)&&(tRecognizeCharacterRET != 0)
            &&(tAssembleTextRET != 0)&&(tGenerateAudioRET != 0)&&(tAdjustVolumeRET != 0)&&(tIdleRET != 0))
    {
        perror("ERROR: Failed Creating Thread.");
        return 0;
    }
    else
        return 1;
}

bool CScope::run()
{
    extern pthread_t tAcquireImageID, tDetectCharacterID, tRecognizeCharacterID,
        tAssembleTextID, tGenerateAudioID, tAdjustVolumeID, tIdleID;

    if(initThreads())
    {
        pthread_join(tAcquireImageID, nullptr);
        pthread_join(tDetectCharacterID, nullptr);
        pthread_join(tRecognizeCharacterID, nullptr);
        pthread_join(tAssembleTextID, nullptr);
        pthread_join(tGenerateAudioID, nullptr);
        pthread_join(tAdjustVolumeID, nullptr);
        pthread_join(tIdleID, nullptr);

        return 1;
    }
    else
        return 0;
}
