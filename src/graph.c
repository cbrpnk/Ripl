#include <stdlib.h>
#include <string.h>
#include "graph.h"

int ripl_graph_init(Ripl_Graph *graph, unsigned int sample_rate, unsigned int buffer_size)
{
    graph->sample_rate = sample_rate;
    graph->buffer_size = buffer_size;
    graph->n_nodes = 0;
    graph->signal_path_length = 0;
    ripl_node_init(&graph->master_in, graph, RIPL_DUMMY);
    ripl_node_init(&graph->master_out, graph, RIPL_DUMMY);
    return 0;
}

int ripl_graph_cleanup(Ripl_Graph *graph)
{
    for(int i=0; i<graph->n_nodes; ++i) {
        ripl_node_cleanup(graph->nodes[i]);
        free(graph->nodes[i]);
    }
    
    ripl_node_cleanup(&graph->master_in);
    ripl_node_cleanup(&graph->master_out);
    return 0;
}

int ripl_graph_gen_sigpath(Ripl_Graph *graph)
{
    ripl_graph_gen_sigpath_recursive(graph, &graph->master_out);
    return 0;
}

int ripl_graph_gen_sigpath_recursive(Ripl_Graph *graph, Ripl_Node *root)
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
            ripl_graph_gen_sigpath_recursive(graph, root->inputs[i].node);
        }
    }
    
    // We went through all out inputs, add ourself to the signal path
    graph->signal_path[graph->signal_path_length] = root;
    graph->signal_path_length++;
    return 0;
}

int ripl_graph_process(Ripl_Graph *graph, const Ripl_Audio_Buffer *in,
                       Ripl_Audio_Buffer *out)
{
    // TODO Set master_in to in

    for(int i=0; i<graph->signal_path_length; ++i) {
        ripl_node_process(graph->signal_path[i]);
    }
    
    // Copy the output buffer of the node connected to master out into out
    memcpy(out->buffer, graph->master_out.inputs[0].node->processor.output.buffer,
           out->size * sizeof(Ripl_Audio_Frame));
    return 0;
}

Ripl_Node *ripl_graph_add(Ripl_Graph *graph, Ripl_Processor_Type type)
{
    Ripl_Node *node = malloc(sizeof(Ripl_Node));
    graph->nodes[graph->n_nodes++] = node;
    ripl_node_init(node, graph, type);
    return node;
}
