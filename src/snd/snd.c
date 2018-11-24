#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "snd.h"
#include "audio.h"

Snd *snd_init(unsigned int sample_rate, unsigned int buffer_size,
                void (*user_callback)(void *), void *user_data)
{
    srand(time(NULL));
    
    Snd *snd = malloc(sizeof(Snd));
    
    snd_backend_init(&snd->backend, snd_callback, (void *) snd);
    snd_backend_open_device(&snd->backend, sample_rate, buffer_size);
    
    snd_graph_init(&snd->graph, sample_rate, buffer_size);
    
    snd->playing = 0;
    snd->play_head = 0;
    snd->time = 0;
    snd->beat = 0;
    snd->bpm = 140;
    snd->user_callback = user_callback;
    snd->user_data = user_data;
    
    return snd;
}

int snd_cleanup(Snd *snd)
{
    if(snd != NULL) {
        snd_stop(snd);

        snd_backend_close_device(&snd->backend);
        snd_backend_cleanup(&snd->backend);

        snd_graph_cleanup(&snd->graph);

        free(snd);
    }
    return 0;
}

int snd_play(Snd *snd)
{
    if(snd != NULL) {
        snd->playing = 1;
    }
    return 0;
}

int snd_stop(Snd *snd)
{
    if(snd != NULL) {
        snd->playing = 0;
    }
    return 0;
}

int snd_callback(void *user_data, const Snd_Audio_Buffer *in, Snd_Audio_Buffer *out)
{
    Snd *snd = (Snd *) user_data;
    
    // Silence buffer
    memset(out->buffer, 0, sizeof(Snd_Audio_Frame) * out->size);
    
    if(snd->playing) {
        snd->user_callback(snd->user_data);
        snd_graph_process(&snd->graph, (const Snd_Audio_Buffer *) in, out);
        // Advance time forward by the size of the buffer
        snd->play_head += out->size;
        snd->time = (float) snd->play_head / snd->graph.sample_rate;
        snd->beat = snd->time / 60.0 * snd->bpm;
    }
    return 0;
}

Snd_Node *snd_master_in(Snd *snd)
{
    return snd->graph.master_in;
}

Snd_Node *snd_master_out(Snd *snd)
{
    return snd->graph.master_out;
}

Snd_Node *snd_osc(Snd *snd)
{
    return snd_graph_add(&snd->graph, SND_OSC);
}

// Reset Graph
int snd_reset_graph(Snd *snd)
{
    return snd_graph_reset(&snd->graph);
}

// Shortcut to snd_node_send
int snd_send(Snd_Node *source, Snd_Node *dest, unsigned int dest_input)
{
    return snd_node_send(source, dest, dest_input);
}

// Shortcut to snd_node_set
int snd_set(Snd_Node *node, unsigned int param, float value)
{
    return snd_node_set_param(node, param, value);
}
