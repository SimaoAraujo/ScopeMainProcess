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
    cout << "CButton::CButton() Initiated!" << endl;
    initSignal();
}

void CButton::ISR(int signal)
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

    /*********************** WHY???? *******************/

    cout << "CButton::initSignal() Initiated!" << endl;

    return;
}
