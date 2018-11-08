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
    
    ripl_mixer_init(&ripl->mixer, sample_rate);
    
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

int ripl_callback(const void *input, void *output, unsigned long n_frames, void *user_data)
{
    Ripl *ripl = (Ripl *) user_data;
    const float *in = (const float *) input;
    float *out = (float *) output;
    
    if(ripl->playing) {
        for(int ch=0; ch<RIPL_MIXER_CHANNEL; ++ch) {
            Ripl_Mixer_Channel *channel = &(ripl->mixer.ch[ch]);
            for(int sl=0; sl<(channel->n_modules); ++sl) {
                Ripl_Module *module = channel->modules[sl];
                if(module && module->on) {
                    module->process_func(module->params, out, n_frames);
                }
            }
        }
    }
    return 0;
}
