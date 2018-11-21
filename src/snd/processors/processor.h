#ifndef SND_PROCESSOR_H
#define SND_PROCESSOR_H

#include "../audio.h"

typedef enum Snd_Processor_Type {
    SND_DUMMY = 0,
    SND_OSC
} Snd_Processor_Type;

typedef struct Snd_Processor {
    void *obj;
    Snd_Param **params;
    int (*process_func)(void*, const Snd_Audio_Buffer**, Snd_Audio_Buffer*);
    unsigned int n_inputs;
    // Array of inputs to be passed to process func
    Snd_Audio_Buffer **inputs;
    // Output to be passed to process_func
    Snd_Audio_Buffer output;
} Snd_Processor;

int snd_processor_init(Snd_Processor *processor, Snd_Processor_Type type,
                        unsigned int sample_rate, unsigned int buffer_size);
int snd_processor_cleanup(Snd_Processor *processor);
int snd_processor_set_input(Snd_Processor *processor, unsigned int index,
                             Snd_Audio_Buffer *input);
int snd_processor_set_param(Snd_Processor *processor, unsigned int param, float value);
int snd_processor_process(Snd_Processor *processor);

// Init functions for all our processor types
int snd_processor_dummy_init(Snd_Processor *processor, unsigned int sample_rate);

#endif
