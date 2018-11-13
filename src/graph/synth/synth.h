#ifndef RIPL_SYNTH_H
#define RIPL_SYNTH_H

#include "../../audio.h"

typedef enum Ripl_Synth_Input {
    RIPL_SYNTH_FM = 0,
    RIPL_SYNTH_IN_COUNT
} Ripl_Synth_Input;

typedef enum Ripl_Synth_Param_Name {
    RIPL_SYNTH_FREQ = 0,
    RIPL_SYNTH_PARAM_COUNT
} Ripl_Synth_Param_Name;

typedef struct Ripl_Synth {
    // Array of pointer to parameters controllable by the user
    float *params[RIPL_SYNTH_PARAM_COUNT];
    float freq;
    unsigned int sample_rate;
    float phase;
} Ripl_Synth;

int ripl_synth_init(Ripl_Synth *synth, unsigned int sample_rate);
int ripl_synth_cleanup(Ripl_Synth *synth);
int ripl_synth_process(void *synth, const Ripl_Audio_Buffer **in,
                       Ripl_Audio_Buffer *out);

#endif
