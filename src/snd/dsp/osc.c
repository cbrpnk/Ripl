#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "osc.h"

#define PI  3.14159265359
#define TAU 6.28318530718

int sndOscInit(SndOsc *osc, unsigned int sampleRate)
{
    osc->sampleRate = sampleRate;
    osc->phase = 0.0f;
    osc->freq = 120.0f;
    return 0;
}

int sndOscCleanup(SndOsc *osc)
{
    return 0;
}

int sndOscProcess(void *data, const SndAudioBuffer **in, SndAudioBuffer *out)
{
    SndOsc *osc = (SndOsc *) data;
    
    float phaseIncrement = (TAU * osc->freq) / osc->sampleRate;
    
    for(int i=0; i<out->size; ++i) {
        float sample = sin(osc->phase);
        osc->phase += phaseIncrement;
        if(osc->phase >= TAU) osc->phase -= TAU;
        
        out->buffer[i].left = sample;
        out->buffer[i].right = sample;
    }
    return 0;
}
