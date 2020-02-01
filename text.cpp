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
    string create = "/etc/SCOPE/record" + to_string(0) + "/" + name + ".txt";

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

    // Open input image with leptonica library
    Mat image = imread("/etc/SCOPE/record0/image.jpeg");
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
        pthread_cond_wait(&condAssembleText, &mutexAssembleText);

        printf("text\n");
        pthread_mutex_lock(&mutexText);
        CText::getInstance(0)->assemble();
        pthread_mutex_unlock(&mutexText);

        pthread_cond_signal(&condGenerateAudio);
    }
}
