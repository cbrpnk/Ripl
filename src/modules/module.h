#ifndef RIPL_MODULE_H
#define RIPL_MODULE_H

// Forward declaration
typedef struct Ripl Ripl;

typedef struct Ripl_Module {
    Ripl* ripl;
    int (*process_func)(void *data, float *output, unsigned long nFrames);
    int on;
} Ripl_Module;

int ripl_module_init(Ripl* ripl, Ripl_Module *module,
                     int (*process_func)(void *data, float *output, unsigned long nFrames));

#endif
