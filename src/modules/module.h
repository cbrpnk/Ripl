#ifndef RIPL_MODULE_H
#define RIPL_MODULE_H

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

#endif
