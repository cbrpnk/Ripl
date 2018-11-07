#ifndef RIPL_MIXER_H
#define RIPL_MIXER_H

#include "module.h"

#define RIPL_MIXER_MODULES_PER_CHANNEL 8
#define RIPL_MIXER_CHANNEL             32

typedef struct Ripl_Mixer_Channel {
    Ripl_Module *modules[RIPL_MIXER_MODULES_PER_CHANNEL];
    unsigned int n_modules;
} Ripl_Mixer_Channel;

typedef struct Ripl_Mixer {
    Ripl_Mixer_Channel ch[RIPL_MIXER_CHANNEL];
    Ripl_Mixer_Channel master;
} Ripl_Mixer;

int ripl_mixer_init(Ripl_Mixer *mixer);
int ripl_mixer_add(Ripl_Mixer *mixer, unsigned int channel, Ripl_Module* module);

#endif
