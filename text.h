#ifndef CTEXT_H
#define CTEXT_H

#include <iostream>
#include <semaphore.h>
#include <fstream>
#include <string>
#include <stdlib.h>

using namespace std;

class CText
{
public:
    static CText* getInstance(int);
    static void* tAssembleText(void*);
private:
    static CText *instance;
    static int recordCount;

    CText(int);
    ~CText();
    void createFile(string, string);
};

#endif
