#include <stdlib.h>
#include "node.h"
#include "synth.h"

int ripl_node_init(Ripl_Node *node, Ripl_Node_Type type, unsigned int sample_rate,
                     unsigned int buffer_size,
                     int (process_func)(void*, const Ripl_Audio_Buffer*,
                                        Ripl_Audio_Buffer*))
{
    void *params;
    switch(type) {
    case RIPL_SYNTH:
        params = malloc(sizeof(Ripl_Synth));
        ripl_synth_init((Ripl_Synth *) params, node, sample_rate);
    }
    
    node->type = type;
    node->params = params;
    node->input = NULL;
    // The buffer should be twice as big as buffer_size since we have 2 channels
    node->output_buffer.size = buffer_size;
    node->output_buffer.buffer = (Ripl_Audio_Frame *)
                                   malloc(sizeof(Ripl_Audio_Frame) * buffer_size);
    node->process_func = process_func;
    node->on = 1;
    return 0;
}

int ripl_node_cleanup(Ripl_Node *node)
{
    switch(node->type) {
    case RIPL_SYNTH:
        ripl_synth_cleanup((Ripl_Synth *) node->params);
        free(node->params);
        break;
    }
        
    free(node->output_buffer.buffer);
    return 0;
}
