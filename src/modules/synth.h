#ifndef RIPL_SYNTH_H
#define RIPL_SYNTH_H

#include "module.h"
#include "../dsp/synth.h"

typedef struct Ripl_Sytnh {
    Ripl_Module module;
    Dsp_Synth params;
} Ripl_Synth;

int ripl_synth_init(Ripl_Synth *synth, unsigned int sample_rate, unsigned int buffer_size);
int ripl_synth_cleanup(Ripl_Synth *synth);

#endif
