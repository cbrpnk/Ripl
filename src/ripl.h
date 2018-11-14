#ifndef RIPL_H
#define RIPL_H

#include "backend/backend.h"
#include "graph.h"

#define RIPL_MAX_NODES 256

typedef struct Ripl {
    unsigned int playing;
    Ripl_Backend backend;
    Ripl_Graph   graph;
} Ripl;

Ripl *ripl_init(unsigned int sample_rate, unsigned int buffer_size);
int   ripl_cleanup(Ripl *ripl);
int   ripl_play(Ripl *ripl);
int   ripl_stop(Ripl *ripl);
int   ripl_callback(void *user_data, const Ripl_Audio_Buffer *in, Ripl_Audio_Buffer *out);

// Add nodes to graph
Ripl_Node *ripl_master_in(Ripl *ripl);
Ripl_Node *ripl_master_out(Ripl *ripl);
Ripl_Node *ripl_osc(Ripl *ripl);

// Shortcut to ripl_node_send
int ripl_send(Ripl_Node *source, Ripl_Node *dest, unsigned int dest_input);

// Shortcut to ripl_node_set
int ripl_set(Ripl_Node *node, unsigned int param, float value);

#endif
