#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "dummy.h"

int sndDummyInit(SndDummy *dummy, unsigned int sampleRate)
{
    dummy->sampleRate = sampleRate;
    dummy->dummy = 0;
    return 0;
}

int sndDummyCleanup(SndDummy *dummy)
{
    return 0;
}

int sndDummyProcess(void *data, const SndAudioBuffer **in, SndAudioBuffer *out)
{
    return 0;
}
