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

bool CCamera::capture(int cameraId)
{
    CRecord oRecord;

    int recordCount = oRecord.create();
    CImage *oImage = CImage::getInstance(0);
    Mat frame;

    oImages.push_back(oImage);

    videoCapture.open(cameraId);
    if(videoCapture.isOpened())
    {
        if(videoCapture.read(frame))
            oImage->save(frame);
        else
            cout << "ERROR Capturing Frame!" << endl;

        videoCapture.release();
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
    extern pthread_mutex_t mutexCamera;
    extern sem_t semInterpretCharacter;

    //sem_wait(&semInterpretCharacter);
    pthread_mutex_lock(&mutexCamera);
    CCamera::getInstance()->capture(0);
    pthread_mutex_unlock(&mutexCamera);
    //sem_post(&semInterpretCharacter);

    pthread_exit(nullptr);
}
