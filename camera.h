#ifndef CCAMERA_H
#define CCAMERA_H

#include "image.h"

class CCamera
{
public:
    CCamera();
    CImage fTakeImage();
private:
    CImage oImage;
};

#endif // CCAMERA_H
