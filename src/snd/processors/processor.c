#include <stdlib.h>
#include "processor.h"
#include "dummy.h"
#include "osc.h"

int sndProcessorInit(SndProcessor *processor, SndProcessorType type,
                        unsigned int sampleRate, unsigned int bufferSize)
{
    switch(type) {
    case SND_DUMMY:
        sndProcessorDummyInit(processor, sampleRate);
        break;
    case SND_OSC:
        sndProcessorOscInit(processor, sampleRate);
        break;
    }
    processor->inputs = malloc(sizeof(SndAudioBuffer*) * processor->nInputs);
    processor->output.size = bufferSize;
    processor->output.buffer = malloc(sizeof(SndAudioFrame) * bufferSize);
    
    return 0;
}

int sndProcessorCleanup(SndProcessor *processor)
{
    free(processor->obj);
    free(processor->params); // Initialized in the specific processor init function
    free(processor->inputs);
    free(processor->output.buffer);
    return 0;
}

int sndProcessorSetInput(SndProcessor *processor, unsigned int index,
                             SndAudioBuffer *input)
{
    processor->inputs[index] = input;
    return 0;
}

int sndProcessorSetParam(SndProcessor *processor, unsigned int param, float value)
{
    *(processor->params[param]) = value;
    return 0;
}

int sndProcessorProcess(SndProcessor *processor)
{
    processor->processFunc(processor->obj, (const SndAudioBuffer **) processor->inputs,
                            &processor->output);
    return 0;
}
