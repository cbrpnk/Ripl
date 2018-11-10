#ifndef RIPL_MIXER_H
#define RIPL_MIXER_H

#include "mixer_channel.h"
#include "audio.h"

#define RIPL_MIXER_CHANNEL 32

// Ripl_Mixer manages a bunch of channel
typedef struct Ripl_Mixer {
    unsigned int sample_rate;
    unsigned int buffer_size;
    Ripl_Mixer_Channel ch[RIPL_MIXER_CHANNEL];
} Ripl_Mixer;

int ripl_mixer_init(Ripl_Mixer *mixer, unsigned int sample_rate, unsigned int buffer_size);
int ripl_mixer_cleanup(Ripl_Mixer *mixer);
int ripl_mixer_process(Ripl_Mixer *mixer, const Ripl_Audio_Buffer* in,
                       Ripl_Audio_Buffer *out);

// Add Modules
Ripl_Synth *ripl_mixer_add_synth(Ripl_Mixer *mixer, unsigned int channel);

#endif
