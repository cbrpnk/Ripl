#ifndef RIPL_MIXER_H
#define RIPL_MIXER_H

#include "modules/module.h"
#include "modules/synth.h"

#define RIPL_MIXER_MODULES_PER_CHANNEL 8
#define RIPL_MIXER_CHANNEL             32

typedef struct Ripl_Mixer_Channel {
    Ripl_Module *modules[RIPL_MIXER_MODULES_PER_CHANNEL];
    unsigned int n_modules;
} Ripl_Mixer_Channel;

typedef struct Ripl_Mixer {
    unsigned int sample_rate;
    Ripl_Mixer_Channel ch[RIPL_MIXER_CHANNEL];
    Ripl_Mixer_Channel master;
} Ripl_Mixer;

int ripl_mixer_init(Ripl_Mixer *mixer, unsigned int sample_rate);
int ripl_mixer_cleanup(Ripl_Mixer *mixer);

// Add Modules
Ripl_Synth *ripl_mixer_add_synth(Ripl_Mixer *mixer, unsigned int channel);

#endif
