#ifndef SND_PROCESSOR_DUMMY_H
#define SND_PROCESSOR_DUMMY_H

#include "../dsp/dummy.h"

typedef struct SndProcessor SndProcessor;

#define SND_DUMMY_PARAM_COUNT 1

int sndProcessorDummyInit(SndProcessor *processor, unsigned int sampleRate);

#endif
