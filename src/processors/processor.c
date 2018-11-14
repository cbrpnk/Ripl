#include <stdlib.h>
#include "processor.h"
#include "dummy.h"
#include "osc.h"

int ripl_processor_init(Ripl_Processor *processor, Ripl_Processor_Type type,
                        unsigned int sample_rate, unsigned int buffer_size)
{
    switch(type) {
    case RIPL_DUMMY:
        ripl_processor_dummy_init(processor, sample_rate);
        break;
    case RIPL_OSC:
        ripl_processor_osc_init(processor, sample_rate);
        break;
    }
    processor->inputs = malloc(sizeof(Ripl_Audio_Buffer*) * processor->n_inputs);
    processor->output.size = buffer_size;
    processor->output.buffer = malloc(sizeof(Ripl_Audio_Frame) * buffer_size);
}

int ripl_processor_cleanup(Ripl_Processor *processor)
{
    free(processor->obj);
    free(processor->params); // Initialized in the specific processor init function
    free(processor->inputs);
    free(processor->output.buffer);
    return 0;
}

int ripl_processor_set_input(Ripl_Processor *processor, unsigned int index,
                             Ripl_Audio_Buffer *input)
{
    processor->inputs[index] = input;
    return 0;
}

int ripl_processor_set_param(Ripl_Processor *processor, unsigned int param, float value)
{
    *(processor->params[param]) = value;
    return 0;
}

int ripl_processor_process(Ripl_Processor *processor)
{
    processor->process_func(processor->obj, (const Ripl_Audio_Buffer **) processor->inputs,
                            &processor->output);
    return 0;
}
