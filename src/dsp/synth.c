#include <stdlib.h>
#include "synth.h"

int ripl_dsp_synth_init(Ripl_Dsp_Synth *synth)
{
    synth->dummy = 0;
    return 0;
}

int ripl_dsp_synth_cleanup(Ripl_Dsp_Synth *synth)
{
    return 0;
}

int ripl_dsp_synth_process(void *data, float *output, unsigned long n_frames)
{
    Ripl_Dsp_Synth *synth = (Ripl_Dsp_Synth *) data;
    for(int i=0; i<n_frames*2; ++i) {
        float sample = (float) rand() / RAND_MAX;
        output[i] = sample;
        output[i] = sample;
    }
    return 0;
}
