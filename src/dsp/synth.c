#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "synth.h"

int ripl_dsp_synth_init(Ripl_Dsp_Synth *synth)
{
    synth->phase = 0.0f;
    synth->freq = 120.0f;
    return 0;
}

int ripl_dsp_synth_cleanup(Ripl_Dsp_Synth *synth)
{
    return 0;
}

int ripl_dsp_synth_process(void *data, float *output, unsigned long n_frames)
{
    Ripl_Dsp_Synth *synth = (Ripl_Dsp_Synth *) data;
    
    unsigned int sample_rate = 44100; // TODO Do not hardcode this
    float phase_increment = (2.0f * M_PI * synth->freq) / sample_rate;
    
    for(int i=0; i<n_frames; ++i) {
        //float sample = (float) rand() / RAND_MAX;
        float sample = sin(synth->phase);
        synth->phase += phase_increment;
        
        output[i*2] = sample;
        output[i*2+1] = sample;
    }
    return 0;
}
