#ifndef SND_DUMMY_H
#define SND_DUMMY_H

#include "../audio.h"

//
// Dummy 
// a node that does nothing
//

#define SND_DUMMY_IN_COUNT 1

typedef struct Snd_Dummy {
    float sample_rate;
    float dummy;
} Snd_Dummy;

int snd_dummy_init(Snd_Dummy *dummy, unsigned int sample_rate);
int snd_dummy_cleanup(Snd_Dummy *dummy);
int snd_dummy_process(void *dummy, const Snd_Audio_Buffer **in,
                       Snd_Audio_Buffer *out);

#endif
