#include <stdlib.h>
#include "mixer.h"
#include "../audio.h"
#include "processor.h"

int snd_processor_mixer_init(Snd_Processor *processor, unsigned int sample_rate)
{
    processor->obj = malloc(sizeof(Snd_Mixer));
    snd_osc_init((Snd_Osc *) processor->obj, sample_rate);
    processor->process_func = snd_osc_process;
    processor->n_inputs = SND_OSC_IN_COUNT;
    
    // Params
    Snd_Osc *osc = (Snd_Osc *) processor->obj;
    processor->params = malloc(SND_OSC_PARAM_COUNT * sizeof(Snd_Param *));
    processor->params[SND_OSC_FREQ] = &osc->freq;
    return 0;
}
