#ifndef RIPL_MODULE_H
#define RIPL_MODULE_H

#include "../audio.h"

typedef enum Ripl_Module_Type {
    RIPL_SYNTH = 0
} Ripl_Module_Type;


// Forward declaration;
typedef struct Ripl_Module Ripl_Module;

typedef struct Ripl_Module {
    Ripl_Module_Type type;
    void *params;
    int (*process_func)(void*, const Ripl_Audio_Buffer*, Ripl_Audio_Buffer*);
    Ripl_Module *input;
    Ripl_Audio_Buffer output_buffer;
    int on;
} Ripl_Module;

int ripl_module_init(Ripl_Module *module, Ripl_Module_Type type, unsigned int sample_rate,
                     unsigned int buffer_size,
                     int (process_func)(void*, const Ripl_Audio_Buffer*,
                                        Ripl_Audio_Buffer*));
int ripl_module_cleanup(Ripl_Module *module);

#endif
