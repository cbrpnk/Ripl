#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "snd.h"
#include "audio.h"

Snd *sndInit(unsigned int sampleRate, unsigned int bufferSize,
                void (*userCallback)(void *), void *userData)
{
    srand(time(NULL));
    
    Snd *snd = malloc(sizeof(Snd));
    
    sndBackendInit(&snd->backend, sndCallback, (void *) snd);
    sndBackendOpenDevice(&snd->backend, sampleRate, bufferSize);
    
    sndGraphInit(&snd->graph, sampleRate, bufferSize);
    
    snd->playing = 0;
    snd->playHead = 0;
    snd->time = 0;
    snd->beat = 0;
    snd->bpm = 140;
    snd->userCallback = userCallback;
    snd->userData = userData;
    
    return snd;
}

int sndCleanup(Snd *snd)
{
    if(snd != NULL) {
        sndStop(snd);

        sndBackendCloseDevice(&snd->backend);
        sndBackendCleanup(&snd->backend);

        sndGraphCleanup(&snd->graph);

        free(snd);
    }
    return 0;
}

int sndPlay(Snd *snd)
{
    if(snd != NULL) {
        snd->playing = 1;
    }
    return 0;
}

int sndStop(Snd *snd)
{
    if(snd != NULL) {
        snd->playing = 0;
    }
    return 0;
}

int sndCallback(void *userData, const SndAudioBuffer *in, SndAudioBuffer *out)
{
    Snd *snd = (Snd *) userData;
    
    // Silence buffer
    memset(out->buffer, 0, sizeof(SndAudioFrame) * out->size);
    
    if(snd->playing) {
        if(snd->userCallback) {
            snd->userCallback(snd->userData);
        }
        sndGraphProcess(&snd->graph, (const SndAudioBuffer *) in, out);
        // Advance time forward by the size of the buffer
        snd->playHead += out->size;
        snd->time = (float) snd->playHead / snd->graph.sampleRate;
        snd->beat = snd->time / 60.0 * snd->bpm;
    }
    return 0;
}

SndNode *sndMasterIn(Snd *snd)
{
    return snd->graph.masterIn;
}

SndNode *sndMasterOut(Snd *snd)
{
    return snd->graph.masterOut;
}

SndNode *sndOsc(Snd *snd)
{
    return sndGraphAdd(&snd->graph, SND_OSC);
}

// Reset Graph
int sndResetGraph(Snd *snd)
{
    return sndGraphReset(&snd->graph);
}

// Shortcut to sndNodeSend
int sndSend(SndNode *source, SndNode *dest, unsigned int destInput)
{
    return sndNodeSend(source, dest, destInput);
}

// Shortcut to sndNodeSet
int sndSet(SndNode *node, unsigned int param, float value)
{
    return sndNodeSetParam(node, param, value);
}
