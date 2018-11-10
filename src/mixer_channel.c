#include <stdlib.h>
#include "mixer_channel.h"

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
        ripl_module_cleanup(module);
        free(module);
    }
    
    return 0;
}

int ripl_mixer_channel_add(Ripl_Mixer_Channel *ch, Ripl_Module *module)
{
    ch->modules[ch->n_modules] = module;
    ch->n_modules++;
    ch->output = &(module->output_buffer);
    return 0;
}

int ripl_mixer_channel_process(Ripl_Mixer_Channel *ch, const Ripl_Audio_Buffer *in,
                               Ripl_Audio_Buffer *out)
{
    if(ch->n_modules > 0) {
        // This pointer points to the channel input for the first itteration of the loop
        // bellow. For each subsequent itteration it will point to the previous module's
        // output_buffer
        const Ripl_Audio_Buffer *in_ptr = in;
        Ripl_Module *module;
        
        for(int i=0; i<ch->n_modules; ++i) {
            module = ch->modules[i];
            if(module->on) {
                module->process_func(module->params, in, &module->output_buffer);
                in_ptr = &module->output_buffer;
            }
        }
        
        // Sum the ouput into out, we overright the data alreay put in there by privous
        // channels
        for(int i=0; i<out->size; ++i) {
            out->buffer[i].left += ch->output->buffer[i].left;
            out->buffer[i].right += ch->output->buffer[i].right;
        }
    }
    return 0;
}
