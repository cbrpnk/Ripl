#ifndef RIPL_PROCESSOR_H
#define RIPL_PROCESSOR_H

#include "../audio.h"
#include "osc/osc.h"
#include "dummy/dummy.h"

typedef enum Ripl_Processor_Type {
    RIPL_DUMMY = 0,
    RIPL_OSC
} Ripl_Processor_Type;

typedef struct Ripl_Processor {
    void *obj;
    float **params;
    int (*process_func)(void*, const Ripl_Audio_Buffer**, Ripl_Audio_Buffer*);
    unsigned int n_inputs;
    // Array of inputs to be passed to process func
    Ripl_Audio_Buffer **inputs;
    // Output to be passed to process_func
    Ripl_Audio_Buffer output;
} Ripl_Processor;

int ripl_processor_init(Ripl_Processor *processor, Ripl_Processor_Type type,
                        unsigned int sample_rate, unsigned int buffer_size);
int ripl_processor_cleanup(Ripl_Processor *processor);
int ripl_processor_set_input(Ripl_Processor *processor, unsigned int index,
                             Ripl_Audio_Buffer *input);
int ripl_processor_process(Ripl_Processor *processor);

// Init functions for all our processor types
int ripl_processor_dummy_init(Ripl_Processor *processor, unsigned int sample_rate);
int ripl_processor_osc_init(Ripl_Processor *processor, unsigned int sample_rate);

#endif
