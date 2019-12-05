#ifndef CBUTTON_H
#define CBUTTON_H

#include <iostream>
#include <string>

using namespace std;

class CButton
{
public:
    static CButton *getInstance();
private:
    static CButton *instance;

    CButton();
    ~CButton();
};

#endif
