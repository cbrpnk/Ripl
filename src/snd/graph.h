#ifndef SND_GRAPH_H
#define SND_GRAPH_H

#include "node.h"

#define SND_MAX_NODES 256

//
// Snd_Graph
// Manages Snd_Nodes and computes the signal that goes through them
//
typedef struct Snd_Graph {
    unsigned int sample_rate;
    unsigned int buffer_size;
    // All the nodes we manage
    unsigned int n_nodes;
    Snd_Node *nodes[SND_MAX_NODES];
    // Ordered nodes that should be processed when calling snd_graph_process
    unsigned int signal_path_length;
    Snd_Node *signal_path[SND_MAX_NODES];
    // Where the signal graph touches the external world
    Snd_Node *master_in;
    Snd_Node *master_out;
} Snd_Graph;

int snd_graph_init(Snd_Graph *graph, unsigned int sample_rate, unsigned int buffer_size);
int snd_graph_cleanup(Snd_Graph *graph);

// Put the nodes in the order they should be executed in
int snd_graph_gen_sigpath(Snd_Graph *graph);
int snd_graph_gen_sigpath_recursive(Snd_Graph *graph, Snd_Node *root);

// Goes through the graph and execute the nodes.
int snd_graph_process(Snd_Graph *graph, const Snd_Audio_Buffer *in,
                       Snd_Audio_Buffer *out);

// Add nodes
Snd_Node *snd_graph_add(Snd_Graph *graph, Snd_Processor_Type type);

// Get node by id
Snd_Node *snd_graph_get_node(Snd_Graph *graph, Snd_Node_Id id);

#endif
