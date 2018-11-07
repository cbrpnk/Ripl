#ifndef RIPL_MODULE_H
#define RIPL_MODULE_H

#include "dsp/synth.h"

// Forward declaration
typedef struct Ripl Ripl;

typedef enum Ripl_Module_Type {
    RIPL_SYNTH = 0
} Ripl_Module_Type;

typedef struct Ripl_Module {
    Ripl* ripl;
    Ripl_Module_Type type;
    int (*process_func)(void *data, float *output, unsigned long nFrames);
    int on;
} Ripl_Module;

int ripl_module_init(Ripl *ripl, Ripl_Module_Type type, Ripl_Module *module,
                     int (*process_func)(void *data, float *output, unsigned long nFrames));
int ripl_module_cleanup(Ripl_Module *module);

// TODO Sym is a test
typedef struct Ripl_Sytnh {
    Ripl_Module module;
    Ripl_Dsp_Synth params;
} Ripl_Synth;
Ripl_Synth *ripl_synth_init(Ripl *ripl);
int         ripl_synth_cleanup(Ripl_Synth *synth);

#endif
