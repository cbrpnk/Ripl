#ifndef RIPL_H
#define RIPL_H

#include "backend/backend.h"
#include "mixer.h"
#include "modules/synth.h"

#define RIPL_MAX_MODULES 256 // TODO Make that infinite

typedef struct Ripl {
    unsigned int playing;
    unsigned int sampling_rate;
    unsigned int buffer_size;
    Ripl_Module *modules[RIPL_MAX_MODULES];
    unsigned int n_modules;
    Ripl_Backend backend;
    Ripl_Mixer   mixer;
} Ripl;

Ripl *ripl_init();
int   ripl_cleanup(Ripl *ripl);
int   ripl_play(Ripl *ripl);
int   ripl_stop(Ripl *ripl);
int   ripl_callback(const void *input, void *output, unsigned long n_frames,
                    void *user_data);

// Adds a module baes on a Ripl_Module_Type to a channel. This will be called by the
// add functions bellow.
Ripl_Module *ripl_add_module(Ripl *ripl, Ripl_Module_Type type,  unsigned int channel);

// Adds different modules and returns a nice pointer to the specific modules
Ripl_Synth *ripl_add_synth(Ripl *ripl, unsigned int channel);

#endif
