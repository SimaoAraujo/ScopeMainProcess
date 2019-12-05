#include "camera.h"

CCamera* CCamera::instance = nullptr;

CCamera* CCamera::getInstance()
{
    if(!instance)
        instance = new CCamera();
    return instance;
}

CCamera::CCamera()
{
    config();
}

CCamera::~CCamera()
{
    close();
}

void CCamera::config()
{
    videoCapture.set(CV_CAP_PROP_FRAME_WIDTH ,640);
    videoCapture.set(CV_CAP_PROP_FRAME_HEIGHT,480);
    videoCapture.set(CV_CAP_PROP_BRIGHTNESS, 100);
    videoCapture.set(CV_CAP_PROP_EXPOSURE, 20);
    videoCapture.set(CV_CAP_PROP_CONTRAST, 0);
    videoCapture.set(CV_CAP_PROP_SATURATION, 0);
}

bool CCamera::open(int cameraId)
{
    return videoCapture.open(cameraId);
}

void CCamera::close()
{
   videoCapture.release();
}

bool CCamera::isOpened(void)
{
    return videoCapture.isOpened();
}

bool CCamera::capture(int cameraId)
{
    Mat frame;
    CImage *oImage = new CImage();

    open(cameraId);
    if(isOpened())
    {
        videoCapture.read(frame);
        oImage->newInstance(frame);
        close();
        return true;
    }
    return false;
}

void *CCamera::tAcquireImage(void *ptr)
{
    extern pthread_mutex_t mutexCamera;
    CCamera *oCamera = CCamera::getInstance();

    pthread_mutex_lock(&mutexCamera);
    oCamera->capture(0);
    pthread_mutex_unlock(&mutexCamera);

    /**************************** is it needed pthread_exit()? *********************************/
}
