#include "mixer.h"

int ripl_mixer_init(Ripl_Mixer *mixer)
{
    for(int i=0; i<RIPL_MIXER_CHANNEL; ++i) {
        for(int j=0; j<RIPL_MIXER_MODULES_PER_CHANNEL; ++j) {
            mixer->ch[i].n_modules = 0;
        }
    }
    return 0;
}

int ripl_mixer_add(Ripl_Mixer *mixer, unsigned int channel, Ripl_Module* module)
{
    // TODO Remove limit on modules
    Ripl_Mixer_Channel *ch = &(mixer->ch[channel]);
    if(ch->n_modules < RIPL_MIXER_MODULES_PER_CHANNEL) {
        ch->modules[ch->n_modules] = module;
        ch->n_modules++;
    }
    
    return 0;
}
