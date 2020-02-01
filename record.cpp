#include "record.h"

int CRecord::recordCount = 0;

CRecord::CRecord()
{

}

CRecord::~CRecord()
{

}

int CRecord::create()
{
    string directory = "/etc/SCOPE/record";
    string createDirectory = "mkdir " + directory + to_string(recordCount);
    system(createDirectory.c_str());

    return ++recordCount;
}

CImage* CRecord::getCImage()
{
    CImage* oImage = CImage::getInstance(this->recordCount);
    return oImage;
}

CText* CRecord::getCText()
{
    CText* oText = CText::getInstance(this->recordCount);
    return oText;
}

CAudio* CRecord::getCAudio()
{
    CAudio* oAudio = CAudio::getInstance(this->recordCount);
    return oAudio;
}
