#include <stdlib.h>
#include "module.h"

int ripl_module_init(Ripl_Module_Type type, Ripl_Module *module,
                     int (*process_func)(void *data, float *output, unsigned long nFrames))
{
    module->type = type;
    module->process_func = process_func;
    module->on = 1;
    return 0;
}

int ripl_module_cleanup(Ripl_Module *module) {
    return 0;
}
