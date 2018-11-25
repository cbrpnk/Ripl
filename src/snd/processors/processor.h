#ifndef SND_PROCESSOR_H
#define SND_PROCESSOR_H

#include "../audio.h"

typedef enum SndProcessorType {
    SND_DUMMY = 0,
    SND_OSC
} SndProcessorType;

typedef struct SndProcessor {
    void *obj;
    SndParam **params;
    int (*processFunc)(void*, const SndAudioBuffer**, SndAudioBuffer*);
    unsigned int nInputs;
    // Array of inputs to be passed to process func
    SndAudioBuffer **inputs;
    // Output to be passed to processFunc
    SndAudioBuffer output;
} SndProcessor;

int sndProcessorInit(SndProcessor *processor, SndProcessorType type,
                        unsigned int sampleRate, unsigned int bufferSize);
int sndProcessorCleanup(SndProcessor *processor);
int sndProcessorSetInput(SndProcessor *processor, unsigned int index,
                             SndAudioBuffer *input);
int sndProcessorSetParam(SndProcessor *processor, unsigned int param, float value);
int sndProcessorProcess(SndProcessor *processor);

// Init functions for all our processor types
int sndProcessorDummyInit(SndProcessor *processor, unsigned int sampleRate);

#endif
