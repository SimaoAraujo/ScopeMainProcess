#include "audio.h"

CAudio::CAudio()
{

}

void *CAudio::tGenerateAudio(void *ptr)
{
    while (1)
    {
        cout << "Arrived at: tGenerateAudio" << endl;
    }
}
