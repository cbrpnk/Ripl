#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "ripl.h"
#include "audio.h"

Ripl *ripl_init(unsigned int sample_rate, unsigned int buffer_size)
{
    srand(time(NULL));
    
    Ripl *ripl = (Ripl*) malloc(sizeof(Ripl));
    ripl->playing = 0;
    ripl->sample_rate = sample_rate;
    ripl->buffer_size = buffer_size;
    
    // TODO Merge these into ripl_backend_init();
    ripl_backend_init(&ripl->backend, ripl_callback, (void *) ripl);
    ripl_backend_open_device(&ripl->backend, ripl->sample_rate, ripl->buffer_size);
    
    ripl_graph_init(&ripl->graph, sample_rate, buffer_size);
    
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

int ripl_callback(const void *in, void *out, unsigned long n_frames, void *user_data)
{
    Ripl *ripl = (Ripl *) user_data;
    Ripl_Audio_Buffer in_buffer = {.size = n_frames, .buffer = (Ripl_Audio_Frame *) in};
    Ripl_Audio_Buffer out_buffer = {.size = n_frames, .buffer = (Ripl_Audio_Frame *) out};
    
    // Silence buffer
    memset(out_buffer.buffer, 0, sizeof(Ripl_Audio_Frame) * n_frames);
    
    if(ripl->playing) {
        ripl_graph_process(&ripl->graph, (const Ripl_Audio_Buffer *) &in_buffer,
                           &out_buffer);
    }
    return 0;
}

Ripl_Node *ripl_add(Ripl *ripl, Ripl_Node_Type type)
{
    return ripl_graph_add(&ripl->graph, type);
}

Ripl_Node *ripl_master_in(Ripl *ripl)
{
    return &ripl->graph.master_in;
}

Ripl_Node *ripl_master_out(Ripl *ripl)
{
    return &ripl->graph.master_out;
}

Ripl_Node *ripl_synth(Ripl *ripl)
{
    return ripl_add(ripl, RIPL_SYNTH);
}

// Shortcut to ripl_node_send
int ripl_send(Ripl *ripl, Ripl_Node *source, Ripl_Node *dest, unsigned int dest_input)
{
    return ripl_graph_send(&ripl->graph, source, dest, dest_input);
}

// Shortcut to ripl_node_set
int ripl_set(Ripl_Node *node, unsigned int param, float value)
{
    return ripl_node_set(node, param, value);
}
