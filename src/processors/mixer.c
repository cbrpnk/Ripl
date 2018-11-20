#include <stdlib.h>
#include "mixer.h"
#include "../audio.h"
#include "processor.h"

int ripl_processor_mixer_init(Ripl_Processor *processor, unsigned int sample_rate)
{
    processor->obj = malloc(sizeof(Ripl_Mixer));
    ripl_osc_init((Ripl_Osc *) processor->obj, sample_rate);
    processor->process_func = ripl_osc_process;
    processor->n_inputs = RIPL_OSC_IN_COUNT;
    
    // Params
    Ripl_Osc *osc = (Ripl_Osc *) processor->obj;
    processor->params = malloc(RIPL_OSC_PARAM_COUNT * sizeof(Ripl_Param *));
    processor->params[RIPL_OSC_FREQ] = &osc->freq;
    return 0;
}
