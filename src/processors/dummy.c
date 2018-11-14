#include <stdlib.h>
#include "dummy.h"
#include "../audio.h"
#include "processor.h"

int ripl_processor_dummy_init(Ripl_Processor *processor, unsigned int sample_rate)
{
    processor->obj = malloc(sizeof(Ripl_Dummy));
    ripl_dummy_init((Ripl_Dummy *) processor->obj, sample_rate);
    processor->process_func = ripl_dummy_process;
    processor->n_inputs = RIPL_DUMMY_IN_COUNT;
    
    // Params
    Ripl_Dummy *dummy = (Ripl_Dummy *) processor->obj;
    processor->params = malloc(RIPL_DUMMY_PARAM_COUNT * sizeof(Ripl_Param *));
    processor->params[0] = &dummy->dummy;
    return 0;
}
