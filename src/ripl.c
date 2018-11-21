#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "ripl.h"
#include "audio.h"

Ripl *ripl_init(unsigned int sample_rate, unsigned int buffer_size,
                void (*user_callback)(void *), void *user_data)
{
    srand(time(NULL));
    
    Ripl *ripl = malloc(sizeof(Ripl));
    
    ripl_backend_init(&ripl->backend, ripl_callback, (void *) ripl);
    ripl_backend_open_device(&ripl->backend, sample_rate, buffer_size);
    
    ripl_graph_init(&ripl->graph, sample_rate, buffer_size);
    
    ripl->playing = 0;
    ripl->play_head = 0;
    ripl->time = 0;
    ripl->beat = 0;
    ripl->bpm = 140;
    ripl->user_callback = user_callback;
    ripl->user_data = user_data;
    
    return ripl;
}

int ripl_cleanup(Ripl *ripl)
{
    ripl_stop(ripl);
    
    ripl_backend_close_device(&ripl->backend);
    ripl_backend_cleanup(&ripl->backend);
    
    ripl_graph_cleanup(&ripl->graph);
    
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

int ripl_callback(void *user_data, const Ripl_Audio_Buffer *in, Ripl_Audio_Buffer *out)
{
    Ripl *ripl = (Ripl *) user_data;
    
    // Silence buffer
    memset(out->buffer, 0, sizeof(Ripl_Audio_Frame) * out->size);
    
    if(ripl->playing) {
        ripl->user_callback(ripl->user_data);
        ripl_graph_process(&ripl->graph, (const Ripl_Audio_Buffer *) in, out);
        // Advance time forward by the size of the buffer
        ripl->play_head += out->size;
        ripl->time = (float) ripl->play_head / ripl->graph.sample_rate;
        ripl->beat = ripl->time / 60.0 * ripl->bpm;
    }
    return 0;
}

Ripl_Node *ripl_master_in(Ripl *ripl)
{
    return ripl->graph.master_in;
}

Ripl_Node *ripl_master_out(Ripl *ripl)
{
    return ripl->graph.master_out;
}

Ripl_Node *ripl_osc(Ripl *ripl)
{
    return ripl_graph_add(&ripl->graph, RIPL_OSC);
}

// Shortcut to ripl_node_send
int ripl_send(Ripl_Node *source, Ripl_Node *dest, unsigned int dest_input)
{
    return ripl_node_send(source, dest, dest_input);
}

// Shortcut to ripl_node_set
int ripl_set(Ripl_Node *node, unsigned int param, float value)
{
    return ripl_node_set_param(node, param, value);
}
