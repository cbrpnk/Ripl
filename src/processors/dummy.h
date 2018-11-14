#ifndef RIPL_PROCESSOR_DUMMY_H
#define RIPL_PROCESSOR_DUMMY_H

#include "../dsp/dummy.h"

typedef struct Ripl_Processor Ripl_Processor;

#define RIPL_DUMMY_PARAM_COUNT 1

int ripl_processor_dummy_init(Ripl_Processor *processor, unsigned int sample_rate);

#endif
