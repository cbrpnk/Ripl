#ifndef RIPL_SYNTH_H
#define RIPL_SYNTH_H

#include "module.h"

typedef struct Ripl_Synth {
    Ripl_Module module;
    unsigned char dummy; // TODO Replace me
} Ripl_Synth;

Ripl_Synth *ripl_synth_init(Ripl *ripl);
int ripl_synth_cleanup(Ripl_Synth *synth);

int ripl_synth_process(void *synth, float *output, unsigned long n_frames);

#endif
