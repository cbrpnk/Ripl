#ifndef SND_PROCESSOR_OSC_H
#define SND_PROCESSOR_OSC_H

#include "../dsp/osc.h"

typedef struct Snd_Processor Snd_Processor;

typedef enum Snd_Processor_Osc_Param {
    SND_OSC_FREQ = 0,
    SND_OSC_PARAM_COUNT
} Snd_Processor_Osc_Param;

int snd_processor_osc_init(Snd_Processor *processor, unsigned int sample_rate);

#endif
