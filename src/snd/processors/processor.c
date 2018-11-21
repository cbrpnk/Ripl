#include <stdlib.h>
#include "processor.h"
#include "dummy.h"
#include "osc.h"

int snd_processor_init(Snd_Processor *processor, Snd_Processor_Type type,
                        unsigned int sample_rate, unsigned int buffer_size)
{
    switch(type) {
    case SND_DUMMY:
        snd_processor_dummy_init(processor, sample_rate);
        break;
    case SND_OSC:
        snd_processor_osc_init(processor, sample_rate);
        break;
    }
    processor->inputs = malloc(sizeof(Snd_Audio_Buffer*) * processor->n_inputs);
    processor->output.size = buffer_size;
    processor->output.buffer = malloc(sizeof(Snd_Audio_Frame) * buffer_size);
    
    return 0;
}

int snd_processor_cleanup(Snd_Processor *processor)
{
    free(processor->obj);
    free(processor->params); // Initialized in the specific processor init function
    free(processor->inputs);
    free(processor->output.buffer);
    return 0;
}

int snd_processor_set_input(Snd_Processor *processor, unsigned int index,
                             Snd_Audio_Buffer *input)
{
    processor->inputs[index] = input;
    return 0;
}

int snd_processor_set_param(Snd_Processor *processor, unsigned int param, float value)
{
    *(processor->params[param]) = value;
    return 0;
}

int snd_processor_process(Snd_Processor *processor)
{
    processor->process_func(processor->obj, (const Snd_Audio_Buffer **) processor->inputs,
                            &processor->output);
    return 0;
}
