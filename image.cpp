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
    cvtColor(image,image,CV_BGR2GRAY);
    /* save image in Rpi directory: "/etc" as "testCamera.jpeg" */
    imwrite("/etc/testCamera.jpeg", image);
}
