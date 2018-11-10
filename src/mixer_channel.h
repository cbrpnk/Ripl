#ifndef RIPL_MIXER_CHANNEL_H
#define RIPL_MIXER_CHANNEL_H

#include "modules/module.h"
#include "modules/synth.h"
#include "audio.h"

#define RIPL_MIXER_MODULES_PER_CHANNEL 8

// Ripl_Mixer_Channel managed a bunch of modules
typedef struct Ripl_Mixer_Channel {
    Ripl_Module *modules[RIPL_MIXER_MODULES_PER_CHANNEL];
    unsigned int sample_rate;
    unsigned int n_modules;
    // This points to the output buffer of the last module in the chain
    Ripl_Audio_Buffer *output;
} Ripl_Mixer_Channel;

int ripl_mixer_channel_init(Ripl_Mixer_Channel *ch, unsigned int sample_rate,
                            unsigned int buffer_size);
int ripl_mixer_channel_cleanup(Ripl_Mixer_Channel *ch);
int ripl_mixer_channel_add(Ripl_Mixer_Channel *ch, Ripl_Module *module);
int ripl_mixer_channel_process(Ripl_Mixer_Channel *ch, const Ripl_Audio_Buffer *in,
                               Ripl_Audio_Buffer *out);
#endif
