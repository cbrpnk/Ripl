#ifndef RIPL_H
#define RIPL_H

#include "backend/backend.h"
#include "graph/graph.h"

#define RIPL_MAX_NODES 256

typedef struct Ripl {
    unsigned int playing;
    unsigned int sample_rate;
    unsigned int buffer_size;
    Ripl_Backend backend;
    Ripl_Graph   graph;
} Ripl;

Ripl *ripl_init(unsigned int sample_rate, unsigned int buffer_size);
int   ripl_cleanup(Ripl *ripl);
int   ripl_play(Ripl *ripl);
int   ripl_stop(Ripl *ripl);
int   ripl_callback(const void *in, void *out, unsigned long n_frames,
                    void *user_data);

// Add nodes to mixer
Ripl_Node *ripl_add(Ripl *ripl, Ripl_Node_Type);
Ripl_Node *ripl_master_in(Ripl *ripl);
Ripl_Node *ripl_master_out(Ripl *ripl);
Ripl_Node *ripl_osc(Ripl *ripl);

// Shortcut to ripl_node_send
int ripl_send(Ripl *ripl, Ripl_Node *source, Ripl_Node *dest, unsigned int dest_input);

// Shortcut to ripl_node_set
int ripl_set(Ripl_Node *node, unsigned int param, float value);

#endif
