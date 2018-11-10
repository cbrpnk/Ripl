#ifndef RIPL_MIXER_H
#define RIPL_MIXER_H

#include "modules/module.h"
#include "modules/synth.h"

#define RIPL_MIXER_MODULES_PER_CHANNEL 8
#define RIPL_MIXER_CHANNEL             32

// Ripl_Mixer_Channel managed a bunch of modules
typedef struct Ripl_Mixer_Channel {
    Ripl_Module *modules[RIPL_MIXER_MODULES_PER_CHANNEL];
    unsigned int sample_rate;
    unsigned int n_modules;
    float *input_buffer;
    float *output_buffer;
} Ripl_Mixer_Channel;

int ripl_mixer_channel_init(Ripl_Mixer_Channel *ch, unsigned int sample_rate,
                            unsigned int buffer_size);
int ripl_mixer_channel_cleanup(Ripl_Mixer_Channel *ch);
int ripl_mixer_channel_add(Ripl_Mixer_Channel *ch, Ripl_Module *module);
int ripl_mixer_channel_process(Ripl_Mixer_Channel *ch);

// Ripl_Mixer manages a bunch of channel
typedef struct Ripl_Mixer {
    unsigned int sample_rate;
    unsigned int buffer_size;
    Ripl_Mixer_Channel ch[RIPL_MIXER_CHANNEL];
    Ripl_Mixer_Channel master;
} Ripl_Mixer;

int ripl_mixer_init(Ripl_Mixer *mixer, unsigned int sample_rate, unsigned int buffer_size);
int ripl_mixer_cleanup(Ripl_Mixer *mixer);
int ripl_mixer_process(Ripl_Mixer *mixer, const float* in, float *out,
                       unsigned long n_frames);

// Add Modules
Ripl_Synth *ripl_mixer_add_synth(Ripl_Mixer *mixer, unsigned int channel);

#endif
