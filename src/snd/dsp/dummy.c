#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "dummy.h"

int snd_dummy_init(Snd_Dummy *dummy, unsigned int sample_rate)
{
    dummy->sample_rate = sample_rate;
    dummy->dummy = 0;
    return 0;
}

int snd_dummy_cleanup(Snd_Dummy *dummy)
{
    return 0;
}

int snd_dummy_process(void *data, const Snd_Audio_Buffer **in, Snd_Audio_Buffer *out)
{
    return 0;
}
