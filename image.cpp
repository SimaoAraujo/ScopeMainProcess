#include "image.h"
#include <opencv2/opencv.hpp>
#include <algorithm>
#include <string>
#include <vector>
using namespace cv;
using namespace std;

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

    imwrite("/etc/SCOPE/record" + to_string(this->recordCount) + "/image.jpeg", image);

    cout << "image.jpeg saved." << endl;
}
