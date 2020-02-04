#include "text.h"

CText* CText::instance = nullptr;

CText* CText::getInstance()
{
    if(!instance)
        instance = new CText();
    return instance;
}

int CText::recordCount = 0;

CText::CText()
{

}

CText::~CText()
{

}

int CText::getRecord()
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

void CText::createFile(string name, string text)
{
    string create = "/etc/SCOPE/records/record" + to_string(recordCount) + "/" + name + ".txt";

    ofstream outfile (create.c_str());
    outfile << text << endl;
    outfile.close();

    cout << "CText::createFile()" << endl;
}

void CText::assemble()
{
    tesseract::TessBaseAPI *oTesseract = new tesseract::TessBaseAPI();
    // Initialize tesseract-ocr with English, without specifying tessdata path
    if (oTesseract->Init(NULL, "eng", OEM_LSTM_ONLY))
    {
        cout << "Could not initialize tesseract.\n" << endl;
    }
    oTesseract->SetPageSegMode(PSM_AUTO);

    getRecord();
    // Open input image with opencv library
    Mat image = imread("/etc/SCOPE/records/record" + to_string(recordCount) + "/image.jpeg");
    oTesseract->SetImage(image.data, image.cols, image.rows, 3, image.step);
    // Get OCR result
    char* outText = oTesseract->GetUTF8Text();
    createFile("text", outText);

    // Destroy used object and release memory
    oTesseract->End();
    delete oTesseract;
    delete [] outText;
}

void* CText::tAssembleText(void *ptr)
{
    extern sem_t semAssembleText, semGenerateAudio;
    extern pthread_cond_t condAssembleText, condGenerateAudio;
    extern pthread_mutex_t mutexAssembleText, mutexGenerateAudio, mutexText;

    while(1)
    {
        pthread_mutex_lock(&mutexAssembleText);
        pthread_cond_wait(&condAssembleText, &mutexAssembleText);
        pthread_mutex_unlock(&mutexAssembleText);

        pthread_mutex_lock(&mutexText);
        CText::getInstance()->assemble();
        pthread_mutex_unlock(&mutexText);

        pthread_mutex_lock(&mutexGenerateAudio);
        pthread_cond_signal(&condGenerateAudio);
        pthread_mutex_unlock(&mutexGenerateAudio);
    }
}
