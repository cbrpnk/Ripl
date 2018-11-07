#ifndef RIPL_MODULE_SYNTH_H
#define RIPL_MODULE_SYNTH_H

#include "module.h"
#include "../dsp/synth.h"

typedef struct Ripl_Sytnh {
    Ripl_Module module;
    Ripl_Dsp_Synth params;
} Ripl_Synth;

int ripl_synth_init(Ripl_Synth *synth);
int ripl_synth_cleanup(Ripl_Synth *synth);


#endif
