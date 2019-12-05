#include "button.h"

CButton* CButton::instance = nullptr;

CButton* CButton::getInstance()
{
    if(!instance)
        instance = new CButton();
    return instance;
}

CButton::CButton()
{

}
