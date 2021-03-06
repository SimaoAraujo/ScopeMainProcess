#include "button.h"

CButton* CButton::instance = nullptr;

CButton* CButton::getInstance()
{
    if(!instance)
        instance = new CButton();
    return instance;
}

CButton::CButton()
{

}

CButton::buttonState CButton::getButtonsState()
{
    char buttonsState[3] = {1, 1, 1};
    bs = {1, 1, 1};
    FILE* buttonsDeviceDriver;

    buttonsDeviceDriver = fopen ("/dev/buttons", "r");
    if(buttonsDeviceDriver != nullptr)
    {
        fread(buttonsState, sizeof(int), 3, buttonsDeviceDriver);
        fclose (buttonsDeviceDriver);

        bs = {buttonsState[0], buttonsState[1], buttonsState[2]};
        return bs;
    }
    else
    {
        cout << "ERROR: can't open device." << endl;
        return bs;
    }
}

void CButton::ISR(int signal)
{
    extern sem_t semAcquireImage, semIncreaseVolume, semDecreaseVolume;
    extern pthread_cond_t condAcquireImage;
    extern pthread_mutex_t mutexAcquireImage;
    extern bool busy;
    extern pthread_mutex_t mutexBusy;
    static buttonState newButtonState, lastButtonState;
    newButtonState = CButton::getInstance()->getButtonsState();

    if(signal == SIGALRM)
    {
        if(newButtonState.increaseVolumeButton == '0' && lastButtonState.increaseVolumeButton != '0')
        {
            sem_post(&semIncreaseVolume);
            cout << "button: +" << endl;
        }
        else if(newButtonState.decreaseVolumeButton == '0' && lastButtonState.decreaseVolumeButton != '0')
        {
            sem_post(&semDecreaseVolume);
            cout << "button: -" << endl;
        }
        else if(newButtonState.startButton == '0' && lastButtonState.startButton != '0' && busy == false)
        {
            CRecord::getInstance()->createRecord();
            pthread_mutex_lock(&mutexAcquireImage);
            pthread_cond_signal(&condAcquireImage);
            pthread_mutex_unlock(&mutexAcquireImage);
            cout << "button: |>" << endl;
        }
        else if (newButtonState.startButton == '0' && lastButtonState.startButton != '0' && busy == true)
        {
            pthread_mutex_lock(&mutexBusy);
            CProcess::getInstance()->sendDaemonSignal("SIGTTIN");
            pthread_mutex_unlock(&mutexBusy);
        }

        lastButtonState = newButtonState;
    }
}

void CButton::initSignal()
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

    cout << "CButton::initSignal() Initiated!" << endl;
    return;
}
