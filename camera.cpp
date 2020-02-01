#include "camera.h"

CCamera* CCamera::instance = nullptr;

VideoCapture* CCamera::videoCapture = nullptr;

CCamera* CCamera::getInstance()
{
    if(!instance)
        instance = new CCamera();
    return instance;
}

CCamera::CCamera()
{

}

CCamera::~CCamera()
{

}

void CCamera::config()
{
    if(!videoCapture){
        cout << endl << "video capture!!!!!" << endl << endl;
        videoCapture = new VideoCapture;
    }
    videoCapture->set(CV_CAP_PROP_FRAME_WIDTH, 640);
    videoCapture->set(CV_CAP_PROP_FRAME_HEIGHT, 480);
    videoCapture->set(CV_CAP_PROP_BRIGHTNESS, 100);
    videoCapture->set(CV_CAP_PROP_EXPOSURE, 100);
    videoCapture->set(CV_CAP_PROP_CONTRAST, 100);
    videoCapture->set(CV_CAP_PROP_SATURATION, 100);
}

int CCamera::getCameraPid()
{
    FILE *fp;
    char cmdInfo[10] = {};
    char cPid[10] = {};

    /* Open the command for reading. */
    fp = popen("fuser /dev/video0", "r");
    if (fp == nullptr)
    {
        printf("Failed to run command\n" );
        exit(1);
    }

    /* Read the output a line at a time - output it. */
    fgets(cmdInfo, sizeof(cmdInfo), fp);

    /* close */
    pclose(fp);

    cout << cmdInfo << endl;

//    int firstPidIndex = 0;
//    while (cmdInfo[firstPidIndex] == ' ')
//    {
//        firstPidIndex++;
//    }
//    cout << firstPidIndex << endl;

//    int cPidIndex = 0;
//    if()
//        while (cmdInfo[firstPidIndex] != ' ')
//        {
//            cPid[cPidIndex] = cmdInfo[firstPidIndex];
//            cout << "cPid: " << cPid[cPidIndex] << endl;
//            cPidIndex++;
//            firstPidIndex++;
//        }
    int pid = 0;
    pid = atoi(cmdInfo);
    cout << "Camera PID: "<< pid << endl;
    return pid;
}

void CCamera::killProcess()
{
    if(getCameraPid() != 0)
    {
        string signal = "kill " + to_string(getCameraPid());
        system(signal.c_str());
    }
}

bool CCamera::capture(int cameraId)
{
    CRecord oRecord;
    Mat frame;

    //killProcess();

    CImage *oImage = CImage::getInstance(0);
    oImages.push_back(oImage);

    videoCapture->release();
    if(!videoCapture->isOpened())
    {
        videoCapture->open(cameraId);
    }

    if(videoCapture->isOpened())
    {
        if(videoCapture->read(frame))
            oImage->save(frame);
        else
            cout << "ERROR Capturing Frame!" << endl;

        videoCapture->release();
        return true;
    }
    else
    {
        cout << "ERROR Opening Camera!" << endl;
        return false;
    }
}

void* CCamera::tAcquireImage(void *ptr)
{
    extern sem_t semAcquireImage;
    extern pthread_cond_t condAssembleText;
    extern pthread_mutex_t mutexCamera;

    while(1)
    {
        sem_wait(&semAcquireImage);

        printf("acquire\n");
        pthread_mutex_lock(&mutexCamera);
        CAudio::getInstance(0)->sendDaemonSignal("SIGUSR1");
        CCamera::getInstance()->config();
        CCamera::getInstance()->capture(0);
        pthread_mutex_unlock(&mutexCamera);

        pthread_cond_signal(&condAssembleText);
    }
}
