#include <stdlib.h>
#include "node.h"
#include "graph.h"

int ripl_node_init(Ripl_Node *node, Ripl_Graph *owner, Ripl_Processor_Type type)
{
    node->owner = owner;
    ripl_processor_init(&node->processor, type, owner->sample_rate);
    // An array of pointers to nodes
    node->input_nodes = (Ripl_Node **) calloc(node->processor.n_inputs, sizeof(Ripl_Node*));
    // Our output buffer
    node->output.size = owner->buffer_size;
    node->output.buffer = (Ripl_Audio_Frame *)
                          malloc(sizeof(Ripl_Audio_Frame) * owner->buffer_size);
    node->on = 1;
    return 0;
}

int ripl_node_cleanup(Ripl_Node *node)
{
    ripl_processor_cleanup(&node->processor);
    free(node->input_nodes);
    free(node->output.buffer);
    return 0;
}

int ripl_node_process(Ripl_Node *node)
{
    return node->processor.process_func(node->processor.obj,
                                        (const Ripl_Audio_Buffer **) node->input_nodes,
                                        &node->output);
}

int ripl_node_send(Ripl_Node *node, Ripl_Node *dest, unsigned int dest_input)
{
    if(dest_input < dest->processor.n_inputs) {
        dest->input_nodes[dest_input] = node;
    }
    
    // The new node connection implies an update of the signal path
    ripl_graph_gen_sigpath(node->owner);
    return 0;
}

int ripl_node_set(Ripl_Node *node, unsigned int param, float value)
{
    *node->processor.params[param] = value;
    *node->processor.params[param] = value;
    return 0;
}
