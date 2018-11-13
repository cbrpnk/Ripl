#include <stdlib.h>
#include "node.h"
#include "synth/synth.h"
#include "dummy/dummy.h"

int ripl_node_init(Ripl_Node *node, Ripl_Node_Type type, unsigned int sample_rate,
                     unsigned int buffer_size)
{
    node->type = type;
    switch(type) {
    case RIPL_DUMMY:
        node->obj = malloc(sizeof(Ripl_Dummy));
        ripl_dummy_init((Ripl_Dummy *) node->obj);
        node->process_func = ripl_dummy_process;
        node->n_inputs = RIPL_DUMMY_IN_COUNT;
        break;
    case RIPL_SYNTH:
        node->obj = malloc(sizeof(Ripl_Synth));
        ripl_synth_init((Ripl_Synth *) node->obj, sample_rate);
        node->process_func = ripl_synth_process;
        node->n_inputs = RIPL_SYNTH_IN_COUNT;
        break;
    }
    node->params = (float **) &node->obj;
    // An array of pointers to nodes
    node->input_nodes = (Ripl_Node **) calloc(node->n_inputs, sizeof(Ripl_Node*));
    // Our output buffer
    node->output.size = buffer_size;
    node->output.buffer = (Ripl_Audio_Frame *)
                                 malloc(sizeof(Ripl_Audio_Frame) * buffer_size);
    node->on = 1;
    return 0;
}

int ripl_node_cleanup(Ripl_Node *node)
{
    switch(node->type) {
    case RIPL_DUMMY:
        ripl_dummy_cleanup((Ripl_Dummy *) node->obj);
        break;
    case RIPL_SYNTH:
        ripl_synth_cleanup((Ripl_Synth *) node->obj);
        break;
    }
    
    free(node->obj);
    free(node->input_nodes);
    free(node->output.buffer);
    return 0;
}

int ripl_node_process(Ripl_Node *node)
{
    return node->process_func(node->obj, (const Ripl_Audio_Buffer **) node->input_nodes,
                              &node->output);
}

int ripl_node_send(Ripl_Node *node, Ripl_Node *dest, unsigned int dest_input)
{
    if(dest_input < dest->n_inputs) {
        dest->input_nodes[dest_input] = node;
    }
    
    return 0;
}

int ripl_node_set(Ripl_Node *node, unsigned int param, float value)
{
    *node->params[param] = value;
    return 0;
}
