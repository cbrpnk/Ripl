#ifndef RIPL_MODULE_H
#define RIPL_MODULE_H

#include "synth.h"

typedef enum Ripl_Module_Type {
    RIPL_SYNTH = 0
} Ripl_Module_Type;

typedef struct Ripl_Module {
    Ripl_Module_Type type;
    void *params;
    int (*process_func)(void*, const float*, float*, unsigned long);
    float *output_buffer;
    int on;
} Ripl_Module;

int ripl_module_init(Ripl_Module *module, Ripl_Module_Type type, unsigned int sample_rate,
                     unsigned int buffer_size,
                     int (process_func)(void*, const float*, float*, unsigned long));
int ripl_module_cleanup(Ripl_Module *module);

#endif
