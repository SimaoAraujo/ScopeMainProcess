#include "camera.h"

CCamera::CCamera(int id, CImage *oImage): cameraId(id), pImage(oImage)
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
    videoCapture.set(CV_CAP_PROP_EXPOSURE, 30);
    videoCapture.set(CV_CAP_PROP_CONTRAST, 10);
    videoCapture.set(CV_CAP_PROP_SATURATION, 0);
}

bool CCamera::open()
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

bool CCamera::captureFrame()
{
    Mat frame;

    open();
    if(isOpened())
    {
        videoCapture.read(frame);
        pImage->newInstance(frame);
        close();
        return true;
    }
    return false;
}

void CCamera::saveFrame()
{

}
