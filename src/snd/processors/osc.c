#include <stdlib.h>
#include "osc.h"
#include "../audio.h"
#include "processor.h"

int sndProcessorOscInit(SndProcessor *processor, unsigned int sampleRate)
{
    processor->obj = malloc(sizeof(SndOsc));
    sndOscInit((SndOsc *) processor->obj, sampleRate);
    processor->processFunc = sndOscProcess;
    processor->nInputs = SND_OSC_IN_COUNT;
    
    // Params
    SndOsc *osc = (SndOsc *) processor->obj;
    processor->params = malloc(SND_OSC_PARAM_COUNT * sizeof(SndParam *));
    processor->params[SND_OSC_FREQ] = &osc->freq;
    return 0;
}
