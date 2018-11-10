#include <stdlib.h>
#include "module.h"
#include "synth.h"

int ripl_module_init(Ripl_Module *module, Ripl_Module_Type type, unsigned int sample_rate,
                     unsigned int buffer_size,
                     int (process_func)(void*, const Ripl_Audio_Buffer*,
                                        Ripl_Audio_Buffer*))
{
    void *params;
    switch(type) {
    case RIPL_SYNTH:
        params = malloc(sizeof(Ripl_Synth));
        ripl_synth_init((Ripl_Synth *) params, module, sample_rate);
    }
    
    module->type = type;
    module->params = params;
    // The buffer should be twice as big as buffer_size since we have 2 channels
    module->output_buffer.size = buffer_size;
    module->output_buffer.buffer = (Ripl_Audio_Frame *)
                                   malloc(sizeof(Ripl_Audio_Frame) * buffer_size);
    module->process_func = process_func;
    module->on = 1;
    return 0;
}

int ripl_module_cleanup(Ripl_Module *module)
{
    switch(module->type) {
    case RIPL_SYNTH:
        ripl_synth_cleanup((Ripl_Synth *) module->params);
        free(module->params);
        break;
    }
        
    free(module->output_buffer.buffer);
    return 0;
}
