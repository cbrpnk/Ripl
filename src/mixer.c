#include <stdlib.h>
#include "mixer.h"

int ripl_mixer_init(Ripl_Mixer *mixer, unsigned int sample_rate, unsigned int buffer_size)
{
    mixer->sample_rate = sample_rate;
    mixer->buffer_size = buffer_size;
    
    // Setup channels
    for(int i=0; i<RIPL_MIXER_CHANNEL; ++i) {
        ripl_mixer_channel_init(&(mixer->ch[i]), sample_rate, buffer_size);
    }
    return 0;
}

int ripl_mixer_cleanup(Ripl_Mixer *mixer)
{
    for(int i=0; i<RIPL_MIXER_CHANNEL; ++i) {
        ripl_mixer_channel_cleanup(&(mixer->ch[i]));
    }
    return 0;
}

int ripl_mixer_process(Ripl_Mixer *mixer, const float* in, float *out,
                       unsigned long n_frames)
{
    for(int i=0; i<RIPL_MIXER_CHANNEL; ++i) {
        ripl_mixer_channel_process(&(mixer->ch[i]), in, out, n_frames);
    }
}

Ripl_Synth *ripl_mixer_add_synth(Ripl_Mixer *mixer, unsigned int channel)
{
    Ripl_Mixer_Channel *ch = &(mixer->ch[channel]);
    Ripl_Module *module = NULL;
    
    if(ch->n_modules < RIPL_MIXER_MODULES_PER_CHANNEL) {
        module = (Ripl_Module *) malloc(sizeof(Ripl_Module));
        ripl_module_init(module, RIPL_SYNTH,  mixer->sample_rate,
                         mixer->buffer_size, ripl_synth_process);
        ripl_mixer_channel_add(ch, module);
    }
    
    return (Ripl_Synth *) module->params;
}
