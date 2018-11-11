#ifndef RIPL_H
#define RIPL_H

#include "backend/backend.h"
#include "nodes/synth.h"

#define RIPL_MAX_NODES 256

typedef struct Ripl {
    unsigned int playing;
    unsigned int sample_rate;
    unsigned int buffer_size;
    Ripl_Backend backend;
    unsigned int n_nodes;
    Ripl_Node *nodes[RIPL_MAX_NODES];
    Ripl_Node *output_node;
} Ripl;

Ripl *ripl_init(unsigned int sample_rate, unsigned int buffer_size);
int   ripl_cleanup(Ripl *ripl);
int   ripl_play(Ripl *ripl, Ripl_Node *node);
int   ripl_stop(Ripl *ripl);
int   ripl_callback(const void *in, void *out, unsigned long n_frames,
                    void *user_data);

// Add nodes to mixer
Ripl_Synth *ripl_add_synth(Ripl *ripl);

#endif
