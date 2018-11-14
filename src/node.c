#include <stdlib.h>
#include "node.h"
#include "graph.h"

int ripl_node_init(Ripl_Node *node, Ripl_Graph *owner, Ripl_Processor_Type type)
{
    node->owner = owner;
    node->n_inputs = 0;
    node->n_outputs = 0;
    node->inputs = NULL;
    node->outputs = NULL;
    ripl_processor_init(&node->processor, type, owner->sample_rate, owner->buffer_size);
    node->on = 1;
    return 0;
}

int ripl_node_cleanup(Ripl_Node *node)
{
    ripl_processor_cleanup(&node->processor);
    if(node->n_inputs > 0) free(node->inputs);
    if(node->n_outputs > 0) free(node->outputs);
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
    ripl_node_add_output(node, dest, dest_input);
    ripl_node_add_input(dest, node, dest_input);
    ripl_processor_set_input(&dest->processor, dest_input, &node->processor.output);
    
    // The new node connection implies an update of the signal path
    ripl_graph_gen_sigpath(node->owner);
    return 0;
}

int ripl_node_add_input(Ripl_Node *node, Ripl_Node *target, unsigned int processor_input)
{
    node->inputs = realloc(node->inputs, (node->n_inputs+1) * sizeof(Ripl_Edge));
    node->inputs[node->n_inputs].node = target;
    node->inputs[node->n_inputs].processor_input = processor_input;
    node->n_inputs++;
    return 0;
}

int ripl_node_add_output(Ripl_Node *node, Ripl_Node *target, unsigned int processor_input)
{
    node->outputs = realloc(node->outputs, (node->n_outputs+1) * sizeof(Ripl_Edge));
    node->outputs[node->n_outputs].node = target;
    node->outputs[node->n_outputs].processor_input = processor_input;
    node->n_outputs++;
    return 0;
}

int ripl_node_set_param(Ripl_Node *node, unsigned int param, float value)
{
    ripl_processor_set_param(&node->processor, param, value);
    return 0;
}

int ripl_node_on(Ripl_Node *node)
{
    node->on = 1;
    return 0;
}

int ripl_node_off(Ripl_Node *node)
{
    node->on = 0;
    return 0;
}
