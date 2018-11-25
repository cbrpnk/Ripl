#include <stdlib.h>
#include "dummy.h"
#include "../audio.h"
#include "processor.h"

int sndProcessorDummyInit(SndProcessor *processor, unsigned int sampleRate)
{
    processor->obj = malloc(sizeof(SndDummy));
    sndDummyInit((SndDummy *) processor->obj, sampleRate);
    processor->processFunc = sndDummyProcess;
    processor->nInputs = SND_DUMMY_IN_COUNT;
    
    // Params
    SndDummy *dummy = (SndDummy *) processor->obj;
    processor->params = malloc(SND_DUMMY_PARAM_COUNT * sizeof(SndParam *));
    processor->params[0] = &dummy->dummy;
    return 0;
}
