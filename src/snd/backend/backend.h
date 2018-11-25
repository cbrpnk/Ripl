#ifndef SND_BACKEND_H
#define SND_BACKEND_H

#include <portaudio.h>
#include "../audio.h"

typedef struct SndBackend {
    PaStream* stream;
    int (*userCallback)(void *, const SndAudioBuffer*, SndAudioBuffer*);
    void* userData;
} SndBackend;

int sndBackendInit(SndBackend *backend,
                      int (*userCallback)(void *, const SndAudioBuffer*,
                      SndAudioBuffer*), void *userData);
int sndBackendCleanup(SndBackend *backend);
int sndBackendOpenDevice(SndBackend *backend, unsigned int sampleRate,
                      unsigned int bufferSize);
int sndBackendCloseDevice(SndBackend *backend);
int sndBackendCallback(const void *inputBuffer, void *outputBuffer,
                          unsigned long nFrames, const PaStreamCallbackTimeInfo *timeInfo,
                          PaStreamCallbackFlags statusFlags, void *userData);

#endif
