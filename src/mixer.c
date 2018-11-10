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
    ch->input_buffer = (float *) malloc(sizeof(float) * buffer_size *2);
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
    
    free(ch->input_buffer);
    return 0;
}

int ripl_mixer_channel_add(Ripl_Mixer_Channel *ch, Ripl_Module *module)
{
    // TODO
    return 0;
}

int ripl_mixer_channel_process(Ripl_Mixer_Channel *ch)
{
    // TODO
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
    /*
    for(int ch=0; ch<RIPL_MIXER_CHANNEL; ++ch) {
        Ripl_Mixer_Channel *channel = &(mixer->ch[ch]);
        
        // Process channel
        for(int sl=0; sl<(channel->n_modules); ++sl) {
            Ripl_Module *module = channel->modules[sl];
            if(module && module->on) {
                // TODO The input (if not first module should be the previous module's
                // output_buffer
                module->process_func(module->params, in, module->output_buffer,
                                     n_frames);
            }
        }
        
        // Process master channel
        // TODO
    }
    */
}

Ripl_Synth *ripl_mixer_add_synth(Ripl_Mixer *mixer, unsigned int channel)
{
    Ripl_Mixer_Channel *ch = &(mixer->ch[channel]);
    Ripl_Synth *synth = NULL;
    
    if(ch->n_modules < RIPL_MIXER_MODULES_PER_CHANNEL) {
        synth = (Ripl_Synth *) malloc(sizeof(Ripl_Synth));
        ripl_synth_init(synth, mixer->sample_rate, mixer->buffer_size);
        
        ch->modules[ch->n_modules] = (Ripl_Module *) synth;
        ch->n_modules++;
        ch->output_buffer = synth->module.output_buffer;
    }
    
    return synth;
}
