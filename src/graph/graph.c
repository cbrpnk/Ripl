#include <stdlib.h>
#include <string.h>
#include "graph.h"

int ripl_graph_init(Ripl_Graph *graph, unsigned int sample_rate, unsigned int buffer_size)
{
    graph->sample_rate = sample_rate;
    graph->buffer_size = buffer_size;
    graph->n_nodes = 0;
    graph->signal_path_length = 0;
    // TODO The following is too much of a hack for my taste 
    // (Getting a dummy node that does nothing but nevertheless be interconnected in
    // the graph)
    ripl_node_init(&graph->master_in, 0, 0, 0);
    ripl_node_init(&graph->master_out, 0, 0, 0);
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

int ripl_graph_send(Ripl_Graph *graph, Ripl_Node *from, Ripl_Node *to,
                       unsigned int input)
{
    ripl_node_send(from, to, input);
    // We've change the signal path so we reorder
    ripl_graph_gen_sigpath(graph, &graph->master_out);
    return 0;
}

int ripl_graph_gen_sigpath(Ripl_Graph *graph, Ripl_Node *root)
{
    // Recusively go through the graph and build a signal path in a depth first fashion
    for(int i=0; i<root->n_inputs; ++i) {
        if(root->input_nodes[i] != NULL) {
            // Search node in path
            unsigned int in_path = 0;
            for(int j=0; j<graph->signal_path_length; ++j) {
                if(root->input_nodes[i] == graph->signal_path[j]) {
                    in_path = 1;
                    break;
                }
            }
            
            if(!in_path) {
                ripl_graph_gen_sigpath(graph, root->input_nodes[i]);
            }
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
    memcpy(out->buffer, graph->master_out.input_nodes[0]->output.buffer,
           out->size * sizeof(Ripl_Audio_Frame));
    return 0;
}

Ripl_Node *ripl_graph_add(Ripl_Graph *graph, Ripl_Node_Type type)
{
    Ripl_Node *node = (Ripl_Node *) malloc(sizeof(Ripl_Node));
    graph->nodes[graph->n_nodes++] = node;
    ripl_node_init(node, type, graph->sample_rate, graph->buffer_size);
    return node;
}
