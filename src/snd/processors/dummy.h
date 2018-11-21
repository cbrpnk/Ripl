#ifndef SND_PROCESSOR_DUMMY_H
#define SND_PROCESSOR_DUMMY_H

#include "../dsp/dummy.h"

typedef struct Snd_Processor Snd_Processor;

#define SND_DUMMY_PARAM_COUNT 1

int snd_processor_dummy_init(Snd_Processor *processor, unsigned int sample_rate);

#endif
