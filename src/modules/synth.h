#ifndef RIPL_SYNTH_H
#define RIPL_SYNTH_H

#include "module.h"
#include "../audio.h"

typedef struct Ripl_Synth {
    Ripl_Module *module;
    unsigned int sample_rate;
    float phase;
    float freq;
} Ripl_Synth;

int ripl_synth_init(Ripl_Synth *synth, Ripl_Module * module,  unsigned int sample_rate);
int ripl_synth_cleanup(Ripl_Synth *synth);
int ripl_synth_process(void *synth, const Ripl_Audio_Buffer *in,
                       Ripl_Audio_Buffer *out);

#endif
