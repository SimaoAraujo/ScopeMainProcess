#include "image.h"

CImage* CImage::instance = nullptr;

CImage* CImage::getInstance(int recordCount)
{
    if(!instance)
        instance = new CImage(recordCount);
    return instance;
}

int CImage::recordCount = 0;

CImage::CImage(int recordCount)
{
    CImage::recordCount = recordCount;
}

CImage::~CImage()
{

}

void CImage::save(Mat image)
{
    this->image = image;
    cvtColor(image, image, CV_BGR2GRAY);

    imwrite("/etc/Scope/record" + to_string(this->recordCount) + "/image.jpeg", image);
}

void* CImage::tDetectCharacter(void *ptr)
{
    while (1)
    {
        cout << "Arrived at: tDetectCharacter" << endl;
    }
}

void* CImage::tRecognizeCharacter(void *ptr)
{
    while (1)
    {
        cout << "Arrived at: tRecognizeCharacter" << endl;
    }
}
