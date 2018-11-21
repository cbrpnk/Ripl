#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "osc.h"

#define PI  3.14159265359
#define TAU 6.28318530718

int snd_osc_init(Snd_Osc *osc, unsigned int sample_rate)
{
    osc->sample_rate = sample_rate;
    osc->phase = 0.0f;
    osc->freq = 120.0f;
    return 0;
}

int snd_osc_cleanup(Snd_Osc *osc)
{
    return 0;
}

int snd_osc_process(void *data, const Snd_Audio_Buffer **in, Snd_Audio_Buffer *out)
{
    Snd_Osc *osc = (Snd_Osc *) data;
    
    float phase_increment = (TAU * osc->freq) / osc->sample_rate;
    
    for(int i=0; i<out->size; ++i) {
        float sample = sin(osc->phase);
        osc->phase += phase_increment;
        if(osc->phase >= TAU) osc->phase -= TAU;
        
        out->buffer[i].left = sample;
        out->buffer[i].right = sample;
    }
    return 0;
}
