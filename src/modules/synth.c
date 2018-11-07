#include <stdlib.h>
#include "synth.h"

int ripl_synth_init(Ripl_Synth *synth)
{
    ripl_module_init(&synth->module, RIPL_SYNTH, ripl_dsp_synth_process);
    ripl_dsp_synth_init(&synth->params);
    return 0;
}

int ripl_synth_cleanup(Ripl_Synth *synth)
{
    ripl_module_cleanup(&synth->module);
    ripl_dsp_synth_cleanup(&synth->params);
    return 0;
}
