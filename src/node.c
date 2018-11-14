#include <stdlib.h>
#include "node.h"
#include "graph.h"

int ripl_node_init(Ripl_Node *node, Ripl_Graph *owner, Ripl_Processor_Type type)
{
    node->owner = owner;
    ripl_processor_init(&node->processor, type, owner->sample_rate, owner->buffer_size);
    // An array of pointers to nodes
    node->inputs = calloc(node->processor.n_inputs, sizeof(Ripl_Node*));
    node->on = 1;
    return 0;
}

int ripl_node_cleanup(Ripl_Node *node)
{
    ripl_processor_cleanup(&node->processor);
    free(node->inputs);
    return 0;
}

int ripl_node_process(Ripl_Node *node)
{
    if(node->on) {
        ripl_processor_process(&node->processor);
    }
    return 0;
}

int ripl_node_send(Ripl_Node *node, Ripl_Node *dest, unsigned int dest_input)
{
    if(dest_input < dest->processor.n_inputs) {
        dest->inputs[dest_input] = node;
        ripl_processor_set_input(&dest->processor, dest_input, &node->processor.output);
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
