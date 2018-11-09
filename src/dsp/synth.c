#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "synth.h"


int dsp_synth_init(Dsp_Synth *synth, unsigned int sample_rate)
{
    synth->sample_rate = sample_rate;
    synth->phase = 0.0f;
    synth->freq = 120.0f;
    return 0;
}

int dsp_synth_cleanup(Dsp_Synth *synth)
{
    return 0;
}

int dsp_synth_process(void *data, const float *in, float *out, unsigned long n_frames)
{
    Dsp_Synth *synth = (Dsp_Synth *) data;
    
    float phase_increment = (2.0f * M_PI * synth->freq) / synth->sample_rate;
    
    for(int i=0; i<n_frames; ++i) {
        float sample = sin(synth->phase);
        synth->phase += phase_increment;
        
        out[i*2] = sample;
        out[i*2+1] = sample;
    }
    return 0;
}
