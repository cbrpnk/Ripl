#include <stdlib.h>
#include "mixer.h"

//
// Ripl_Mixer_Channel
//

int ripl_mixer_channel_init(Ripl_Mixer_Channel *ch, unsigned int sample_rate,
                            unsigned int buffer_size)
{
    ch->sample_rate = sample_rate;
    ch->n_modules = 0;
    ch->output = NULL;
    return 0;
}

int ripl_mixer_channel_cleanup(Ripl_Mixer_Channel *ch)
{
    for(int i=0; i<ch->n_modules; ++i) {
        Ripl_Module *module = ch->modules[i];
        switch(module->type) {
        case RIPL_SYNTH:
            ripl_synth_cleanup((Ripl_Synth *) module);
            free(module);
            break;
        }
    }
    
    return 0;
}

int ripl_mixer_channel_add(Ripl_Mixer_Channel *ch, Ripl_Module *module)
{
    ch->modules[ch->n_modules] = module;
    ch->n_modules++;
    ch->output = module->output_buffer;
    return 0;
}

#include <stdio.h>
int ripl_mixer_channel_process(Ripl_Mixer_Channel *ch, const float *in, float *out,
                               unsigned int n_frames)
{
    // This pointer points to the channel input for the first itteration of the loop
    // bellow. For each subsequent itteration it will point to the previous module's
    // output_buffer
    const float *in_ptr = in;
    Ripl_Module *module;
    
    if(ch->n_modules > 0) {
        for(int i=0; i<ch->n_modules; ++i) {
            module = ch->modules[i];
            if(module->on) {
                module->process_func(module->params, in, module->output_buffer, n_frames);
                in_ptr = module->output_buffer;
            }
        }
        
        // Sum the ouput into out, we overright the data alreay put in there by privous
        // channels
        for(int i=0; i<n_frames*2; ++i) {
            out[i] += (ch->output)[i];
        }
    }
    return 0;
}

//
// Ripl_Mixer
//
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
    Ripl_Synth *synth = NULL;
    
    if(ch->n_modules < RIPL_MIXER_MODULES_PER_CHANNEL) {
        synth = (Ripl_Synth *) malloc(sizeof(Ripl_Synth));
        ripl_synth_init(synth, mixer->sample_rate, mixer->buffer_size);
        
        ripl_mixer_channel_add(ch, (Ripl_Module *) synth);
    }
    
    return synth;
}
