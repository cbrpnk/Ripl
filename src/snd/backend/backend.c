#include <stdio.h>
#include "backend.h"

int sndBackendInit(SndBackend *backend,
                      int (*userCallback)(void *, const SndAudioBuffer*,
                      SndAudioBuffer*),
                      void *userData)
{
    PaError err = Pa_Initialize();
    if(err != paNoError) {
        printf("sndBackendInit() error: %s\n", Pa_GetErrorText(err));
        return 1;
    }
    
    backend->userCallback = userCallback;
    backend->userData = userData;
    
    return 0;
}

int sndBackendCleanup(SndBackend *backend)
{
    PaError err = Pa_Terminate();
    if(err != paNoError) {
        printf("sndBackendCleanup error: %s\n", Pa_GetErrorText(err));
        return 1;
    }
    return 0;
}

int sndBackendOpenDevice(SndBackend *backend, unsigned int sampleRate,
                             unsigned int bufferSize)
{
    PaError err;
    
    err = Pa_OpenDefaultStream(&backend->stream, 0, 2, paFloat32, sampleRate,
                               bufferSize, sndBackendCallback, backend);
    if(err != paNoError) {
        printf("sndBackendOpenDevice error: %s\n", Pa_GetErrorText(err));
        return 1;
    }
    
    err = Pa_StartStream(backend->stream);
    if(err != paNoError) {
        printf("sndBbackendOpenDevice error: %s\n", Pa_GetErrorText(err));
        return 1;
    }
    return 0;
}

int sndBackendCloseDevice(SndBackend *backend)
{
    Pa_StopStream(backend->stream);
    Pa_CloseStream(backend->stream);
    return 0;
}

int sndBackendCallback(const void *inputBuffer, void *outputBuffer,
                          unsigned long nFrames, const PaStreamCallbackTimeInfo *timeInfo,
                          PaStreamCallbackFlags statusFlags, void *userData)
{
    SndBackend *backend = (SndBackend *) userData;
    SndAudioBuffer in = {
        .size = nFrames,
        .buffer = (SndAudioFrame *) inputBuffer
    };
    SndAudioBuffer out = {
        .size = nFrames,
        .buffer = (SndAudioFrame *) outputBuffer
    };
    
    return backend->userCallback(backend->userData, (const SndAudioBuffer*) &in, &out);
}
