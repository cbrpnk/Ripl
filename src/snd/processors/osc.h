#ifndef SND_PROCESSOR_OSC_H
#define SND_PROCESSOR_OSC_H

#include "../dsp/osc.h"

typedef struct SndProcessor SndProcessor;

typedef enum SndProcessorOscParam {
    SND_OSC_FREQ = 0,
    SND_OSC_PARAM_COUNT
} SndProcessorOscParam;

int sndProcessorOscInit(SndProcessor *processor, unsigned int sampleRate);

#endif
