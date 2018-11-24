#include <stdlib.h>
#include <string.h>
#include "graph.h"

int snd_graph_init(Snd_Graph *graph, unsigned int sample_rate, unsigned int buffer_size)
{
    graph->sample_rate = sample_rate;
    graph->buffer_size = buffer_size;
    graph->n_nodes = 0;
    graph->signal_path_length = 0;
    graph->master_in = snd_graph_add(graph, SND_DUMMY);
    graph->master_out = snd_graph_add(graph, SND_DUMMY);
    return 0;
}

// TODO Reset should be passed sample rate and buffer size, init should only allocate mem
int snd_graph_reset(Snd_Graph *graph)
{
    snd_graph_cleanup(graph);
    snd_graph_init(graph, graph->sample_rate, graph->buffer_size);
    return 0;
}

int snd_graph_cleanup(Snd_Graph *graph)
{
    for(int i=0; i<graph->n_nodes; ++i) {
        snd_node_cleanup(graph->nodes[i]);
        free(graph->nodes[i]);
    }
    return 0;
}

int snd_graph_gen_sigpath(Snd_Graph *graph)
{
    snd_graph_gen_sigpath_recursive(graph, graph->master_out);
    return 0;
}

int snd_graph_gen_sigpath_recursive(Snd_Graph *graph, Snd_Node *root)
{
    // Recusively go through the graph and build a signal path in a depth first fashion
    for(int i=0; i<root->n_inputs; ++i) {
        // Search node in path
        unsigned int in_path = 0;
        for(int j=0; j<graph->signal_path_length; ++j) {
            if(root->inputs[i].node == graph->signal_path[j]) {
                in_path = 1;
                break;
            }
        }
        
        if(!in_path) {
            snd_graph_gen_sigpath_recursive(graph, root->inputs[i].node);
        }
    }
    
    // We went through all out inputs, add ourself to the signal path
    graph->signal_path[graph->signal_path_length] = root;
    graph->signal_path_length++;
    return 0;
}

int snd_graph_process(Snd_Graph *graph, const Snd_Audio_Buffer *in,
                       Snd_Audio_Buffer *out)
{
    // TODO Set master_in to in

    for(int i=0; i<graph->signal_path_length; ++i) {
        snd_node_process(graph->signal_path[i]);
    }
    
    // Copy the output buffer of the node connected to master out into out
    if(graph->master_out->n_inputs > 0) {
        memcpy(out->buffer, graph->master_out->inputs[0].node->processor.output.buffer,
               out->size * sizeof(Snd_Audio_Frame));
    }
    return 0;
}

Snd_Node *snd_graph_add(Snd_Graph *graph, Snd_Processor_Type type)
{
    Snd_Node *node = malloc(sizeof(Snd_Node));
    graph->nodes[graph->n_nodes] = node;
    snd_node_init(node, graph->n_nodes, graph, type);
    graph->n_nodes++;
    return node;
}

Snd_Node *snd_graph_get_node(Snd_Graph *graph, Snd_Node_Id id)
{
    if(id < graph->n_nodes) {
        return graph->nodes[id];
    }
    return NULL;
}
