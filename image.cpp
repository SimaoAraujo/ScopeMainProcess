#include "image.h"

CImage::CImage()
{

}

CImage::CImage(Mat *image)
{
    this->image = *image;
}

CImage::~CImage()
{

}

void CImage::newInstance(Mat &newImage)
{
    this->image = newImage;

    saveNewInstance();
}

void CImage::saveNewInstance()
{
    /* save image in Rpi directory: "/etc/" as "testCamera.jpeg" */
    imwrite("/etc/testCamera.jpeg", image);
}

