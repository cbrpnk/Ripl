#include <stdlib.h>
#include "synth.h"

Ripl_Synth *ripl_synth_init(Ripl *ripl, unsigned int mixer_channel)
{
    Ripl_Synth *synth = (Ripl_Synth *) malloc(sizeof(Ripl_Synth));
    
    ripl_module_init(ripl, &synth->module, ripl_synth_process);
    ripl_mixer_add(&ripl->mixer, mixer_channel, (Ripl_Module *) synth);
    
    return synth;
}

int ripl_synth_cleanup(Ripl_Synth *synth)
{
    free(synth);
    return 0;
}

int ripl_synth_process(void *data, float *output, unsigned long n_frames)
{
    Ripl_Synth *synth = (Ripl_Synth *) data;
    for(int i=0; i<n_frames*2; ++i) {
        float sample = (float) rand() / RAND_MAX;
        output[i] = sample;
        output[i] = sample;
    }
    return 0;
}
