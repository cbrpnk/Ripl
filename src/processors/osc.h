#ifndef RIPL_PROCESSOR_OSC_H
#define RIPL_PROCESSOR_OSC_H

#include "../dsp/osc.h"

typedef struct Ripl_Processor Ripl_Processor;

typedef enum Ripl_Processor_Osc_Param {
    RIPL_OSC_FREQ = 0,
    RIPL_OSC_PARAM_COUNT
} Ripl_Processor_Osc_Param;

int ripl_processor_osc_init(Ripl_Processor *processor, unsigned int sample_rate);

#endif
