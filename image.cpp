#include "image.h"

using namespace cv;
using namespace std;

CImage* CImage::instance = nullptr;

CImage* CImage::getInstance()
{
    if(!instance)
        instance = new CImage();
    return instance;
}

int CImage::recordCount = 0;

CImage::CImage()
{

}

CImage::~CImage()
{

}

int CImage::getRecord()
{
    string sLastRecordCount;
    int iLastRecordCount;

    ifstream lastRecord_in("/etc/SCOPE/lastRecord.txt");
    if(lastRecord_in.is_open())
    {
        getline(lastRecord_in, sLastRecordCount);
        lastRecord_in.close();
        iLastRecordCount = stoi(sLastRecordCount);
        recordCount = iLastRecordCount;
        return recordCount;
    }
    else
    {
        cout << "Unable to open file";
    }
}

void CImage::save(Mat image)
{
    getRecord();
    this->image = image;
    cvtColor(image, image, CV_BGR2GRAY);
    imwrite("/etc/SCOPE/records/record" + to_string(this->recordCount) + "/image.jpeg", image);

    cout << "image.jpeg saved." << endl;
}
