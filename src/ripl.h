#ifndef RIPL_H
#define RIPL_H

#include "backend/backend.h"
#include "mixer.h"

#define RIPL_MAX_MODULES 256

typedef struct Ripl {
    unsigned int playing;
    unsigned int sample_rate;
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

#endif
