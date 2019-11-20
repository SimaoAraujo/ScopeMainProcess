#ifndef CSCOPE_H
#define CSCOPE_H

#include <iostream>
#include <string>
#include "process.h"
#include "button.h"
#include "camera.h"
#include "earphone.h"

using namespace std;

class CScope
{
public:
    CScope();
    void fRun();
private:
    CProcess oProcess;
    CButton oButtons;
//    CCamera oCamera;
    CEarphone oEarphone;
};

#endif // CSCOPE_H
