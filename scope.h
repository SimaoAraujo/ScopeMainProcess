#ifndef CSCOPE_H
#define CSCOPE_H

#include "process.h"
#include "button.h"
#include "camera.h"
#include "earphone.h"

class CScope
{
public:
    CScope();
    void fRun();
private:
    CProcess oProcess;
    CButton oButtons;
    CCamera oCamera;
    CEarphone oEarphone;
};

#endif // CSCOPE_H
