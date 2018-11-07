#ifndef RIPL_STATE_H
#define RIPL_STATE_H

#include "backend/backend.h"
#include "mixer.h"
#include "modules/synth.h"

#define RIPL_MAX_MODULES 256 // TODO Make that infinite

typedef struct Ripl {
    unsigned int playing;
    unsigned int sampling_rate;
    unsigned int buffer_size;
    Ripl_Backend backend;
    Ripl_Mixer   mixer;
} Ripl;

Ripl *ripl_init();
int   ripl_cleanup(Ripl *ripl);
int   ripl_play(Ripl *ripl);
int   ripl_stop(Ripl *ripl);
int   ripl_callback(const void *input, void *output, unsigned long n_frames,
                    void *user_data);

int ripl_add(Ripl *ripl, void *module, unsigned int channel);

#endif
