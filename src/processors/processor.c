#include <stdlib.h>
#include "processor.h"

int ripl_processor_init(Ripl_Processor *processor, Ripl_Processor_Type type,
                        unsigned int sample_rate)
{
    switch(type) {
    case RIPL_DUMMY:
        ripl_processor_dummy_init(processor, sample_rate);
        break;
    case RIPL_OSC:
        ripl_processor_osc_init(processor, sample_rate);
        break;
    }
}

int ripl_processor_cleanup(Ripl_Processor *processor)
{
    free(processor->obj);
    return 0;
}

int ripl_processor_dummy_init(Ripl_Processor *processor, unsigned int sample_rate)
{
    processor->obj = malloc(sizeof(Ripl_Dummy));
    ripl_dummy_init((Ripl_Dummy *) processor->obj);
    processor->params = ((Ripl_Dummy *) processor->obj)->params;
    processor->process_func = ripl_dummy_process;
    processor->n_inputs = RIPL_DUMMY_IN_COUNT;
    return 0;
}

int ripl_processor_osc_init(Ripl_Processor *processor, unsigned int sample_rate)
{
    processor->obj = malloc(sizeof(Ripl_Osc));
    ripl_osc_init((Ripl_Osc *) processor->obj, sample_rate);
    processor->params = ((Ripl_Osc *) processor->obj)->params;
    processor->process_func = ripl_osc_process;
    processor->n_inputs = RIPL_OSC_IN_COUNT;
    return 0;
}
