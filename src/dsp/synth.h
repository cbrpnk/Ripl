#ifndef RIPL_DSP_SYNTH_H
#define RIPL_DSP_SYNTH_H

typedef struct Ripl_Dsp_Synth {
    unsigned char dummy;
} Ripl_Dsp_Synth;

Ripl_Dsp_Synth *ripl_dsp_synth_init();
int             ripl_dsp_synth_cleanup(Ripl_Dsp_Synth *synth);
int             ripl_dsp_synth_process(void *synth, float *output, unsigned long n_frames);

#endif
