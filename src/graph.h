#ifndef RIPL_GRAPH_H
#define RIPL_GRAPH_H

#include "node.h"

#define RIPL_MAX_NODES 256

//
// Ripl_Graph
// Manages Ripl_Nodes and computes the signal that goes through them
//
typedef struct Ripl_Graph {
    // TODO It might be a better idea to have a reference to Ripl
    unsigned int sample_rate;
    unsigned int buffer_size;
    // All the nodes we manage
    unsigned int n_nodes;
    Ripl_Node *nodes[RIPL_MAX_NODES];
    // Ordered nodes that should be processed when calling ripl_graph_process
    unsigned int signal_path_length;
    Ripl_Node *signal_path[RIPL_MAX_NODES+2]; // +2 for master_in and master_out
    // Where the signal graph touches the external world
    Ripl_Node master_in;
    Ripl_Node master_out;
} Ripl_Graph;

int ripl_graph_init(Ripl_Graph *graph, unsigned int sample_rate, unsigned int buffer_size);
int ripl_graph_cleanup(Ripl_Graph *graph);

// Put the nodes in the order they should be executed in
int ripl_graph_gen_sigpath(Ripl_Graph *graph);
int ripl_graph_gen_sigpath_recursive(Ripl_Graph *graph, Ripl_Node *root);

// Goes through the graph and execute the nodes.
int ripl_graph_process(Ripl_Graph *graph, const Ripl_Audio_Buffer *in,
                       Ripl_Audio_Buffer *out);

// Add nodes
Ripl_Node *ripl_graph_add(Ripl_Graph *graph, Ripl_Processor_Type type);

#endif
