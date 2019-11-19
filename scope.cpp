#include "scope.h"

#include "image.h"

CScope::CScope() : oProcess(), oButtons(), oCamera(), oEarphone()
{

}

void CScope::fRun()
{
    this->oProcess.getRecord().oRecord=oCamera.mfTakeImage();
}
