#include <stdlib.h>
#include "node.h"
#include "graph.h"

int snd_node_init(Snd_Node *node, Snd_Node_Id id, Snd_Graph *owner,
                   Snd_Processor_Type type)
{
    node->id = id;
    node->owner = owner;
    node->n_inputs = 0;
    node->n_outputs = 0;
    node->inputs = NULL;
    node->outputs = NULL;
    snd_processor_init(&node->processor, type, owner->sample_rate, owner->buffer_size);
    node->on = 1;
    return 0;
}

int snd_node_cleanup(Snd_Node *node)
{
    snd_processor_cleanup(&node->processor);
    if(node->n_inputs > 0) free(node->inputs);
    if(node->n_outputs > 0) free(node->outputs);
    return 0;
}

int snd_node_process(Snd_Node *node)
{
    if(node->on) {
        snd_processor_process(&node->processor);
    }
    return 0;
}

int snd_node_send(Snd_Node *node, Snd_Node *dest, unsigned int dest_input)
{
    snd_node_add_output(node, dest, dest_input);
    snd_node_add_input(dest, node, dest_input);
    snd_processor_set_input(&dest->processor, dest_input, &node->processor.output);
    
    // The new node connection implies an update of the signal path
    snd_graph_gen_sigpath(node->owner);
    return 0;
}

int snd_node_add_input(Snd_Node *node, Snd_Node *target, unsigned int processor_input)
{
    node->inputs = realloc(node->inputs, (node->n_inputs+1) * sizeof(Snd_Edge));
    node->inputs[node->n_inputs].node = target;
    node->inputs[node->n_inputs].processor_input = processor_input;
    node->n_inputs++;
    return 0;
}

int snd_node_add_output(Snd_Node *node, Snd_Node *target, unsigned int processor_input)
{
    node->outputs = realloc(node->outputs, (node->n_outputs+1) * sizeof(Snd_Edge));
    node->outputs[node->n_outputs].node = target;
    node->outputs[node->n_outputs].processor_input = processor_input;
    node->n_outputs++;
    return 0;
}

int snd_node_set_param(Snd_Node *node, unsigned int param, float value)
{
    snd_processor_set_param(&node->processor, param, value);
    return 0;
}

int snd_node_on(Snd_Node *node)
{
    node->on = 1;
    return 0;
}

int snd_node_off(Snd_Node *node)
{
    node->on = 0;
    return 0;
}
