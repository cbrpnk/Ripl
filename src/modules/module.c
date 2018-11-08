#include "module.h"

int ripl_module_init(Ripl_Module *module, Ripl_Module_Type type, void *params,
                     int (process_func)(void*, float*, unsigned long))
{
    module->type = type;
    module->params = params;
    module->process_func = process_func;
    module->on = 1;
    return 0;
}

int ripl_module_cleanup(Ripl_Module *module)
{
    return 0;
}
