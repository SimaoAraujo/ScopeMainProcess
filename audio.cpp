#include "audio.h"

CAudio::CAudio()
{

}

//add the convertion of text into audio
string CAudio::generateSound()
{
    string soxCommand;
    sox = "sox -m " + this->getSoundFilePath();
    system(soxCommand.c_str());

    pathWaveFile = "PATH????????????????????????????" + to_string(effect) + ".wav";

    return pathWaveFile;
}

void CConvertWav::convertWavFile(string pathNameFile) {

    FILE * wav_in;
    wav_in = fopen(pathNameFile.c_str(),"rb");     // Open wave file in read mode
    wavPtr=&wav;
    if (wav_in)
    {
        fread(wavPtr, 1, sizeof(wav), wav_in);
        wavData=realloc(wavData, wav.subchunk2_size);
        fread(wavData,wav.bits_per_sample/8,wav.subchunk2_size,wav_in);
    }
    else
        perror("Error Open convertWavFile");

    return;
}

void *CAudio::fSoundGenerater(void *ptr)
{
    extern sem_t sUpdateSound;
    extern sem_t *sSoundGeneratorDaemon;
    extern pthread_mutex_t mAbsolutePattern;

    int size, sharedMemorySize, index;
    unsigned int shmdes, mode;
    char* shmptr;
    char *pt;

    char shm_fn[] = "shmDaemon";
    char sem_fn[] = "semaphoreDaemon";

    CGenerateSound *sound = new CGenerateSound();
    CConvertWav wav;

    while (1) {

        sem_wait(&sUpdateSound);


        sound->generateSound();

        /**+++++++++++++++++++Shared Memory+++++++++++++++++++++++*/

        wav.convertWavFile( sound->getPathNameFile());


        size = wav.getSubChunk();
        pt = (char *) &size;
        mode = S_IRWXU|S_IRWXG;
        /* Open the shared memory object */
        if ( (shmdes = shm_open(shm_fn,O_CREAT|O_RDWR|O_TRUNC, mode)) == -1 ) {
             perror("shm_open failure");
             exit(-1);
        }
        /* Preallocate a shared memory area by determine the current
        value of a configurable system limit for pagesize*/
        sharedMemorySize = 4096 * sysconf(_SC_PAGE_SIZE);
        if(ftruncate(shmdes, sharedMemorySize) == -1){
            perror("ftruncate failure");
            exit(-1);
        }
        if((shmptr =(char *)mmap(0, sharedMemorySize, PROT_WRITE|PROT_READ, MAP_SHARED,shmdes,0)) == (caddr_t) -1) {
            perror("mmap failure");
            exit(-1);
        }
        /* Create a semaphore in locked state */
        sSoundGeneratorDaemon = sem_open(sem_fn, O_CREAT, 0644, 0);
        if(sSoundGeneratorDaemon == (void*)-1) {
          perror("sem_open failure");
          exit(-1);
        }

        shmptr[0] = *pt++;
        shmptr[1] = *pt++;
        shmptr[2] = *pt++;
        shmptr[3] = *pt;

        char *bufferOut = (char *) wav.getPCM();

        /* Access to the shared memory area */
        for(index = 4; index < size + 4; index++) {
            shmptr[index]=bufferOut[index - 4];
        }

        /* Release the semaphore lock */
        sem_post(sSoundGeneratorDaemon);
        munmap(shmptr, sharedMemorySize);
        /* Close the shared memory object */
        close(shmdes);
        /* Close the Semaphore */
        sem_close(sSoundGeneratorDaemon);
        /* Delete the shared memory object */
        //shm_unlink(shm_fn);
        /**+++++++++++++END of test of the Shared Memory++++++++++++++++++*/
    }
}
