#include <stdlib.h>
#include "synth.h"

int ripl_synth_init(Ripl_Synth *synth, unsigned int sample_rate)
{
    ripl_module_init(&synth->module, RIPL_SYNTH, &synth->params, dsp_synth_process);
    dsp_synth_init(&synth->params, sample_rate);
    return 0;
}

int ripl_synth_cleanup(Ripl_Synth *synth)
{
    ripl_module_cleanup(&synth->module);
    dsp_synth_cleanup(&synth->params);
    return 0;
}
