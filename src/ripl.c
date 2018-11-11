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
    ripl->n_nodes = 0;
    
    ripl_backend_init(&ripl->backend, ripl_callback, (void *) ripl);
    ripl_backend_open_device(&ripl->backend, ripl->sample_rate, ripl->buffer_size);
    return ripl;
}

int ripl_cleanup(Ripl *ripl)
{
    ripl_stop(ripl);
    ripl_backend_close_device(&ripl->backend);
    ripl_backend_cleanup(&ripl->backend);
    
    for(int i=0; i<ripl->n_nodes; ++i) {
        ripl_node_cleanup(ripl->nodes[i]);
        free(ripl->nodes[i]);
    }
    
    free(ripl);
    return 0;
}

int ripl_play(Ripl *ripl, Ripl_Node *node)
{
    ripl->output_node = node;
    // TODO here build node call order
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
    
    if(ripl->playing && ripl->output_node) {
        // Build Execution stack
        // TODO find something better than to hardcode 100
        Ripl_Node *stack[RIPL_MAX_NODES];
        unsigned int stack_size = 0;
        
        stack[stack_size] = ripl->output_node;
        Ripl_Node *parent = stack[stack_size]->input;
        ++stack_size;
        while(parent) {
            stack[stack_size] = parent;
            ++stack_size;
            parent = stack[stack_size]->input;
        }
        
        // Execute Stack
        Ripl_Audio_Buffer *in_ptr = &in_buffer;
        for(int i=0; i<stack_size; ++i) {
            if(i > 0) {
                // If this is not the first node we want the input to be the previous
                // nodes output
                in_ptr = &(stack[i-1]->output_buffer);
            } 
            
            stack[i]->process_func(stack[i]->params, &in_buffer,
                                   &(stack[i]->output_buffer));
        }
        
        // Copy output node into soundcard buffer
        memcpy(out_buffer.buffer, ripl->output_node->output_buffer.buffer,
               n_frames * sizeof(Ripl_Audio_Frame));
    }
    return 0;
}

Ripl_Synth *ripl_add_synth(Ripl *ripl)
{
    Ripl_Node *node = (Ripl_Node *) malloc(sizeof(Ripl_Node));
    ripl->nodes[ripl->n_nodes++] = node;
    ripl_node_init(node, RIPL_SYNTH,  ripl->sample_rate,
                     ripl->buffer_size, ripl_synth_process);
    return (Ripl_Synth *) node->params;
}
