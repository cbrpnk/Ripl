#include <stdlib.h>
#include "synth.h"

Ripl_Synth *ripl_synth_init()
{
    Ripl_Synth *synth = (Ripl_Synth *) malloc(sizeof(Ripl_Synth));
    
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
