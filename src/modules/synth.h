#ifndef RIPL_SYNTH_H
#define RIPL_SYNTH_H

typedef struct Ripl_Synth {
    unsigned int sample_rate;
    float phase;
    float freq;
} Ripl_Synth;

int ripl_synth_init(Ripl_Synth *synth, unsigned int sample_rate);
int ripl_synth_cleanup(Ripl_Synth *synth);
int ripl_synth_process(void *synth, const float *in, float *out, unsigned long n_frames);

#endif
