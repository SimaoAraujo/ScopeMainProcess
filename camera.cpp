#include "camera.h"

CCamera* CCamera::instance = nullptr;

VideoCapture* CCamera::videoCapture = nullptr;

CCamera* CCamera::getInstance()
{
    if(!instance)
        instance = new CCamera();
    return instance;
}

int CCamera::recordCount = 0;

CCamera::CCamera()
{

}

CCamera::~CCamera()
{

}

void CCamera::config()
{
    if(!videoCapture){
        videoCapture = new VideoCapture;
    }
    videoCapture->set(CV_CAP_PROP_FRAME_WIDTH, 640);
    videoCapture->set(CV_CAP_PROP_FRAME_HEIGHT, 480);
    videoCapture->set(CV_CAP_PROP_BRIGHTNESS, 100);
    videoCapture->set(CV_CAP_PROP_EXPOSURE, 100);
    videoCapture->set(CV_CAP_PROP_CONTRAST, 100);
    videoCapture->set(CV_CAP_PROP_SATURATION, 100);
}

bool CCamera::capture(int cameraId)
{
    Mat frame;
    CRecord::getInstance()->getRecord();
    CImage *oImage = CImage::getInstance();

    videoCapture->release();
    if(!videoCapture->isOpened())
    {
        videoCapture->open(cameraId);
    }

    if(videoCapture->isOpened())
    {
        if(videoCapture->read(frame))
            oImage->save(frame);
        else
            cout << "ERROR Capturing Frame!" << endl;

        videoCapture->release();
        return true;
    }
    else
    {
        cout << "ERROR Opening Camera!" << endl;
        return false;
    }
}

void* CCamera::tAcquireImage(void *ptr)
{
    extern sem_t semAcquireImage;
    extern pthread_cond_t condAcquireImage, condAssembleText;
    extern pthread_mutex_t mutexAcquireImage, mutexCamera, mutexAssembleText;
    extern bool busy;
    extern pthread_mutex_t mutexBusy;

    while(1)
    {
        pthread_mutex_lock(&mutexAcquireImage);
        pthread_cond_wait(&condAcquireImage, &mutexAcquireImage);
        pthread_mutex_unlock(&mutexAcquireImage);
        pthread_mutex_lock(&mutexBusy);
        busy = true;
        pthread_mutex_unlock(&mutexBusy);

        pthread_mutex_lock(&mutexCamera);
        CProcess::getInstance()->sendDaemonSignal("SIGUSR1");
        CCamera::getInstance()->config();
        CCamera::getInstance()->capture(0);
        pthread_mutex_unlock(&mutexCamera);

        pthread_mutex_lock(&mutexAssembleText);
        pthread_cond_signal(&condAssembleText);
        pthread_mutex_unlock(&mutexAssembleText);
    }
}
