#ifndef SND_OSC_H
#define SND_OSC_H

#include "../audio.h"

typedef enum SndOscInput {
    SND_OSC_FM = 0,
    SND_OSC_IN_COUNT
} SndOscInput;

typedef struct SndOsc {
    unsigned int sampleRate;
    float phase;
    SndParam freq;
} SndOsc;

int sndOscInit(SndOsc *osc, unsigned int sampleRate);
int sndSscCleanup(SndOsc *osc);
int sndOscProcess(void *osc, const SndAudioBuffer **in,
                       SndAudioBuffer *out);

#endif
