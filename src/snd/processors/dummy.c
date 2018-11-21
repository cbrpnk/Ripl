#include <stdlib.h>
#include "dummy.h"
#include "../audio.h"
#include "processor.h"

int snd_processor_dummy_init(Snd_Processor *processor, unsigned int sample_rate)
{
    processor->obj = malloc(sizeof(Snd_Dummy));
    snd_dummy_init((Snd_Dummy *) processor->obj, sample_rate);
    processor->process_func = snd_dummy_process;
    processor->n_inputs = SND_DUMMY_IN_COUNT;
    
    // Params
    Snd_Dummy *dummy = (Snd_Dummy *) processor->obj;
    processor->params = malloc(SND_DUMMY_PARAM_COUNT * sizeof(Snd_Param *));
    processor->params[0] = &dummy->dummy;
    return 0;
}
