#ifndef RIPL_H
#define RIPL_H

#include "backend/backend.h"
#include "modules/synth.h"

#define RIPL_MAX_MODULES 256

typedef struct Ripl {
    unsigned int playing;
    unsigned int sample_rate;
    unsigned int buffer_size;
    Ripl_Backend backend;
    unsigned int n_modules;
    Ripl_Module *modules[RIPL_MAX_MODULES];
    Ripl_Module *output_module;
} Ripl;

Ripl *ripl_init(unsigned int sample_rate, unsigned int buffer_size);
int   ripl_cleanup(Ripl *ripl);
int   ripl_play(Ripl *ripl, Ripl_Module *module);
int   ripl_stop(Ripl *ripl);
int   ripl_callback(const void *in, void *out, unsigned long n_frames,
                    void *user_data);

// Add modules to mixer
Ripl_Synth *ripl_add_synth(Ripl *ripl);

#endif
