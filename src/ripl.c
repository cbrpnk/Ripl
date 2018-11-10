#include <stdlib.h>
#include <time.h>

#include "ripl.h"

Ripl *ripl_init(unsigned int sample_rate, unsigned int buffer_size)
{
    srand(time(NULL));
    
    Ripl *ripl = (Ripl*) malloc(sizeof(Ripl));
    ripl->playing = 0;
    ripl->sample_rate = sample_rate;
    ripl->buffer_size = buffer_size;
    
    ripl_mixer_init(&ripl->mixer, sample_rate, buffer_size);
    
    ripl_backend_init(&ripl->backend, ripl_callback, (void *) ripl);
    ripl_backend_open_device(&ripl->backend, ripl->sample_rate, ripl->buffer_size);
    return ripl;
}

int ripl_cleanup(Ripl *ripl)
{
    ripl_stop(ripl);
    ripl_backend_close_device(&ripl->backend);
    ripl_backend_cleanup(&ripl->backend);
    ripl_mixer_cleanup(&ripl->mixer);
    
    free(ripl);
    return 0;
}

int ripl_play(Ripl *ripl)
{
    ripl->playing = 1;
    return 0;
}

int ripl_stop(Ripl *ripl)
{
    ripl->playing = 0;
    return 0;
}

int ripl_callback(const void *in, void *out, unsigned long n_frames, void *user_data)
{
    Ripl *ripl = (Ripl *) user_data;
    const float *input = (const float *) in;
    float *output = (float *) out;
    
    
    // clean the buffer
    for(int i=0; i<n_frames*2; ++i) {
        output[i] = 0;
    }
    
    if(ripl->playing) {
        ripl_mixer_process(&ripl->mixer, input, output, n_frames);
    }
    return 0;
}

Ripl_Synth *ripl_add_synth(Ripl *ripl, unsigned int ch)
{
    return ripl_mixer_add_synth(&ripl->mixer, ch);
}
