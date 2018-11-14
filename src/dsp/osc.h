#ifndef RIPL_OSC_H
#define RIPL_OSC_H

#include "../audio.h"

typedef enum Ripl_Osc_Input {
    RIPL_OSC_FM = 0,
    RIPL_OSC_IN_COUNT
} Ripl_Osc_Input;

typedef struct Ripl_Osc {
    unsigned int sample_rate;
    float phase;
    Ripl_Param freq;
} Ripl_Osc;

int ripl_osc_init(Ripl_Osc *osc, unsigned int sample_rate);
int ripl_osc_cleanup(Ripl_Osc *osc);
int ripl_osc_process(void *osc, const Ripl_Audio_Buffer **in,
                       Ripl_Audio_Buffer *out);

#endif
