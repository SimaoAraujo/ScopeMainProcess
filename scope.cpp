#include "scope.h"

CScope* CScope::instance = nullptr;

CScope* CScope::getInstance()
{
    if(!instance)
        instance = new CScope();
    return instance;
}

static CProcess *oProcess = CProcess::getInstance();
static CButton *oButtons = CButton::getInstance();
static CCamera *oCamera = CCamera::getInstance();
static CEarphone *oEarphone = CEarphone::getInstance();

CScope::CScope(): oProcess(), oButtons(), oCamera(), oEarphone()
{
    //initObjects();
    initSemaphores();
    initMutexes();
    initConditionVariables();
    initSignal();
    initSharedMemory();
}

CScope::~CScope()
{
    extern sem_t semAcquireImage, semIncreaseVolume, semDecreaseVolume, semInterpretCharacter;
    extern sem_t *semAccessAudio;
    extern pthread_mutex_t mutexImage, mutexFrame, mutexCharacters, mutexText, mutexAudio,
        mutexIncrease, mutexDecrease, mutexAcquireDetect, mutexRecognizeAssemble,
        mutexAssembleGenerate;

    sem_destroy(&semAcquireImage);
    sem_destroy(&semIncreaseVolume);
    sem_destroy(&semDecreaseVolume);
    sem_destroy(&semInterpretCharacter);
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

    perror("CScope: Destructor Called!");
}

void CScope::initObjects()
{

}

void CScope::initSemaphores()
{
    extern sem_t semAcquireImage, semIncreaseVolume, semDecreaseVolume, semInterpretCharacter;

    sem_init (&semAcquireImage, 0, 0);
    sem_init (&semIncreaseVolume, 0, 0);
    sem_init (&semDecreaseVolume, 0, 0);
    sem_init (&semInterpretCharacter, 0 , 0);

    /*********************** WHY???? *******************/
    return;
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

    /* a SIGALRM is generated every 8ms */
    setitimer(ITIMER_REAL, &itv, nullptr);

    /*********************** WHY???? *******************/
    return;
}

void CScope::initSharedMemory()
{
    extern sem_t *semAccessAudio;

    char shmName[] = "shmDaemon";
    char semName[] = "semDaemon";

    shm_open(shmName, O_CREAT|O_RDWR|O_TRUNC, S_IRWXU|S_IRWXG);
    semAccessAudio = sem_open(semName, O_CREAT, 0644, 0);
    sem_close(semAccessAudio);

    //system("/etc/ScopeDaemonProcess");
}

void CScope::ISR(int signal)
{
    extern sem_t semAcquireImage, semIncreaseVolume, semDecreaseVolume;

    static int count = 0;

    if(signal == SIGALRM)
    {
        switch (++count)
        {
            case 1:
                sem_post(&semAcquireImage);
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

void *CScope::tIdle(void *ptr)
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

    initObjects();

    pthread_attr_init(&threadAttr);
    pthread_attr_getschedparam(&threadAttr, &threadParam);
    pthread_attr_getschedpolicy(&threadAttr, &threadPolicy);

    setupThread(1, &threadAttr, &threadParam);
    tAcquireImageRET = pthread_create(&tAcquireImageID, nullptr, oProcess->getCRecord()->getCImage()->tAcquireImage, nullptr);

    setupThread(3, &threadAttr, &threadParam);
    tDetectCharacterRET = pthread_create(&tDetectCharacterID, &threadAttr, oProcess->getCRecord()->getCImage()->tDetectCharacter, nullptr);

    setupThread(3, &threadAttr, &threadParam);
    tRecognizeCharacterRET = pthread_create(&tRecognizeCharacterID, &threadAttr, oProcess->getCRecord()->getCImage()->tRecognizeCharacter, nullptr);

    setupThread(4, &threadAttr, &threadParam);
    tAssembleTextRET = pthread_create(&tAssembleTextID, &threadAttr, oProcess->getCRecord()->getCText()->tAssembleText, nullptr);

    setupThread(2, &threadAttr, &threadParam);
    tGenerateAudioRET = pthread_create(&tGenerateAudioID, &threadAttr, oProcess->getCRecord()->getCAudio()->tGenerateAudio, nullptr);

    setupThread(1, &threadAttr, &threadParam);
    tAdjustVolumeRET = pthread_create(&tAdjustVolumeID, &threadAttr, oEarphone->tAdjustVolume, nullptr);

    setupThread(5, &threadAttr, &threadParam);
    tIdleRET = pthread_create(&tIdleID, &threadAttr, this->tIdle, nullptr);

    if((tAcquireImageRET != 0)&&(tDetectCharacterRET != 0)&&(tRecognizeCharacterRET != 0)
            &&(tAssembleTextRET != 0)&&(tGenerateAudioRET != 0)&&(tAdjustVolumeRET != 0)&&(tIdleRET != 0))
    {
        perror("ERROR: Failed Creating Thread.");
        return 1;
    }
    else
        return 0;
}

bool CScope::run()
{
    extern pthread_t tAcquireImageID, tDetectCharacterID, tRecognizeCharacterID,
        tAssembleTextID, tGenerateAudioID, tAdjustVolumeID, tIdleID;

    if(!initThreads())
    {
        pthread_join(tAcquireImageID, nullptr);
        pthread_join(tDetectCharacterID, nullptr);
        pthread_join(tRecognizeCharacterID, nullptr);
        pthread_join(tAssembleTextID, nullptr);
        pthread_join(tGenerateAudioID, nullptr);
        pthread_join(tAdjustVolumeID, nullptr);
        pthread_join(tIdleID, nullptr);

        return 0;
    }
    else
        return 1;
}
