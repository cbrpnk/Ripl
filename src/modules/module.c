#include "module.h"

int ripl_module_init(Ripl* ripl, Ripl_Module_Type type, Ripl_Module *module,
                     int (*process_func)(void *data, float *output, unsigned long nFrames))
{
    module->ripl = ripl;
    module->type = type;
    module->process_func = process_func;
    module->on = 1;
    return 0;
}