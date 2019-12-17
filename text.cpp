#include "text.h"

CText* CText::instance = nullptr;

CText* CText::getInstance(int recordCount)
{
    if(!instance)
        instance = new CText(recordCount);
    return instance;
}

int CText::recordCount = 0;

CText::CText(int recordCount)
{
    CText::recordCount = recordCount;
}

CText::~CText()
{

}

void CText::createFile(string name, string text)
{
    string create = "/etc/Scope/record" + to_string(0) + "/" + name + ".txt";

    ofstream outfile (create.c_str());
    outfile << text << endl;
    outfile.close();

    cout << "CText::createFile()" << endl;
}

void* CText::tAssembleText(void *ptr)
{
    extern sem_t semInterpretCharacter, semGenerateAudio;
    string decodedText = "First decoded test.";
    string helloText = "Hi, my name is SCOPE and i am your reading assistant. Press button to start decoding text.";

        //sem_wait(&semInterpretCharacter);
        CText::getInstance(0)->createFile("helloText", helloText);
        CText::getInstance(0)->createFile("decodedText", decodedText);
        //sem_post(&semGenerateAudio);


    pthread_exit(nullptr);
}
