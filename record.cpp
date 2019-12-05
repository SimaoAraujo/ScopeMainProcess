#include "record.h"

CRecord::CRecord()
{

}

CImage* CRecord::getCImage()
{
    CImage* oImage = new CImage();
    return oImage;
}

CText* CRecord::getCText()
{
    CText* oText = new CText();
    return oText;
}

CAudio* CRecord::getCAudio()
{
    CAudio* oAudio = new CAudio();
    return oAudio;
}
