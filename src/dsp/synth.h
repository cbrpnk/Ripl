#ifndef RIPL_DSP_SYNTH_H
#define RIPL_DSP_SYNTH_H

typedef struct Ripl_Dsp_Synth {
    unsigned int sample_rate;
    float phase;
    float freq;
} Ripl_Dsp_Synth;

int ripl_dsp_synth_init(Ripl_Dsp_Synth *synth, unsigned int sample_rate);
int ripl_dsp_synth_cleanup(Ripl_Dsp_Synth *synth);
int ripl_dsp_synth_process(void *synth, float *output, unsigned long n_frames);

#endif
