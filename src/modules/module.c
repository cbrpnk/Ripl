#include <stdlib.h>
#include "module.h"

int ripl_module_init(Ripl_Module *module, Ripl_Module_Type type, void *params,
                     unsigned int buffer_size,
                     int (process_func)(void*, const float*, float*, unsigned long))
{
    module->type = type;
    module->params = params;
    // The buffer should be twice as big as buffer_size since we have 2 channels
    module->output_buffer = (float *) malloc(sizeof(float) * buffer_size * 2);
    module->process_func = process_func;
    module->on = 1;
    return 0;
}

int ripl_module_cleanup(Ripl_Module *module)
{
    free(module->output_buffer);
    return 0;
}
