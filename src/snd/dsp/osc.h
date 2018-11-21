#ifndef SND_OSC_H
#define SND_OSC_H

#include "../audio.h"

typedef enum Snd_Osc_Input {
    SND_OSC_FM = 0,
    SND_OSC_IN_COUNT
} Snd_Osc_Input;

typedef struct Snd_Osc {
    unsigned int sample_rate;
    float phase;
    Snd_Param freq;
} Snd_Osc;

int snd_osc_init(Snd_Osc *osc, unsigned int sample_rate);
int snd_osc_cleanup(Snd_Osc *osc);
int snd_osc_process(void *osc, const Snd_Audio_Buffer **in,
                       Snd_Audio_Buffer *out);

#endif
