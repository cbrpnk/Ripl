#include <stdlib.h>
#include "mixer.h"

int ripl_mixer_init(Ripl_Mixer *mixer, unsigned int sample_rate)
{
    mixer->sample_rate = sample_rate;
    
    // Setup channels
    for(int i=0; i<RIPL_MIXER_CHANNEL; ++i) {
        for(int j=0; j<RIPL_MIXER_MODULES_PER_CHANNEL; ++j) {
            mixer->ch[i].n_modules = 0;
        }
    }
    return 0;
}

int ripl_mixer_cleanup(Ripl_Mixer *mixer)
{
    for(int i=0; i<RIPL_MIXER_CHANNEL; ++i) {
        Ripl_Mixer_Channel *ch = &(mixer->ch[i]);
        for(int j=0; j<ch->n_modules; ++j) {
            Ripl_Module *module = ch->modules[i];
            switch(module->type) {
            case RIPL_SYNTH:
                ripl_synth_cleanup((Ripl_Synth *) module);
                free(module);
                break;
            }
        }
    }
    
    return 0;
}

int ripl_mixer_process(Ripl_Mixer *mixer, const float* input, float *output,
                       unsigned long n_frames)
{
    for(int ch=0; ch<RIPL_MIXER_CHANNEL; ++ch) {
        Ripl_Mixer_Channel *channel = &(mixer->ch[ch]);
        for(int sl=0; sl<(channel->n_modules); ++sl) {
            Ripl_Module *module = channel->modules[sl];
            if(module && module->on) {
                module->process_func(module->params, output, n_frames);
            }
        }
    }
}

Ripl_Synth *ripl_mixer_add_synth(Ripl_Mixer *mixer, unsigned int channel)
{
    Ripl_Mixer_Channel *ch = &(mixer->ch[channel]);
    Ripl_Synth *synth = NULL;
    
    if(ch->n_modules < RIPL_MIXER_MODULES_PER_CHANNEL) {
        synth = (Ripl_Synth *) malloc(sizeof(Ripl_Synth));
        ripl_synth_init(synth, mixer->sample_rate);
        
        ch->modules[ch->n_modules] = (Ripl_Module *) synth;
        ch->n_modules++;
    }
    
    return synth;
}
