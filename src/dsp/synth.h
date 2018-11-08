#ifndef DSP_SYNTH_H
#define DSP_SYNTH_H

typedef struct Dsp_Synth {
    unsigned int sample_rate;
    float phase;
    float freq;
} Dsp_Synth;

int dsp_synth_init(Dsp_Synth *synth, unsigned int sample_rate);
int dsp_synth_cleanup(Dsp_Synth *synth);
int dsp_synth_process(void *synth, float *output, unsigned long n_frames);

#endif
