#ifndef SND_DUMMY_H
#define SND_DUMMY_H

#include "../audio.h"

//
// Dummy 
// a node that does nothing
//

#define SND_DUMMY_IN_COUNT 1

typedef struct SndDummy {
    float sampleRate;
    float dummy;
} SndDummy;

int sndDummyInit(SndDummy *dummy, unsigned int sampleRate);
int sndDummyCleanup(SndDummy *dummy);
int sndDummyProcess(void *dummy, const SndAudioBuffer **in,
                       SndAudioBuffer *out);

#endif
