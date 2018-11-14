#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "dummy.h"

int ripl_dummy_init(Ripl_Dummy *dummy, unsigned int sample_rate)
{
    dummy->sample_rate = sample_rate;
    dummy->dummy = 0;
    return 0;
}

int ripl_dummy_cleanup(Ripl_Dummy *dummy)
{
    return 0;
}

int ripl_dummy_process(void *data, const Ripl_Audio_Buffer **in, Ripl_Audio_Buffer *out)
{
    return 0;
}
