#include <stdlib.h>
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

int ripl_module_cleanup(Ripl_Module *module) {
    return 0;
}

Ripl_Synth *ripl_synth_init(Ripl *ripl)
{
    Ripl_Synth *synth = (Ripl_Synth *) malloc(sizeof(Ripl_Synth));
    
    synth->module.ripl = ripl;
    synth->module.type = RIPL_SYNTH;
    synth->module.process_func = ripl_dsp_synth_process;
    synth->module.on = 1;
    
    synth->params.dummy = 1;
    
    return synth;

}

int ripl_synth_cleanup(Ripl_Synth *synth)
{
    // TODO
    //ripl_module_cleanup((Ripl_Module *) sym->module);
    //ripl_synth_cleanup((Ripl_Synth *) sym->params);
    free(synth);
    return 0;
}
