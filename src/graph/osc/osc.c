#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "osc.h"

int ripl_osc_init(Ripl_Osc *osc, unsigned int sample_rate)
{
    // Params
    osc->params[RIPL_OSC_FREQ] = &osc->freq;
    
    osc->sample_rate = sample_rate;
    osc->phase = 0.0f;
    osc->freq = 120.0f;
    return 0;
}

int ripl_osc_cleanup(Ripl_Osc *osc)
{
    return 0;
}

int ripl_osc_process(void *data, const Ripl_Audio_Buffer **in, Ripl_Audio_Buffer *out)
{
    Ripl_Osc *osc = (Ripl_Osc *) data;
    
    float phase_increment = (2.0f * M_PI * osc->freq) / osc->sample_rate;
    
    for(int i=0; i<out->size; ++i) {
        float sample = sin(osc->phase);
        osc->phase += phase_increment;
        
        out->buffer[i].left = sample;
        out->buffer[i].right = sample;
    }
    return 0;
}
