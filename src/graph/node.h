#ifndef RIPL_NODE_H
#define RIPL_NODE_H

#include "../audio.h"

typedef enum Ripl_Node_Type {
    RIPL_DUMMY = 0,
    RIPL_SYNTH
} Ripl_Node_Type;

// Forward declaration;
typedef struct Ripl_Node Ripl_Node;

typedef struct Ripl_Node {
    // Output is the first parameter so that we can cast between Ripl_Node*
    // and Ripl_Audio_Buffer*. This is useful when passing the inputs into process_func
    Ripl_Audio_Buffer output;
    unsigned int n_inputs;
    Ripl_Node **input_nodes;
    Ripl_Node_Type type;
    void *obj;
    float **params;
    int (*process_func)(void*, const Ripl_Audio_Buffer**, Ripl_Audio_Buffer*);
    int on;
} Ripl_Node;

int ripl_node_init(Ripl_Node *node, Ripl_Node_Type type, unsigned int sample_rate,
                     unsigned int buffer_size);
int ripl_node_process(Ripl_Node *node);
int ripl_node_cleanup(Ripl_Node *node);
int ripl_node_send(Ripl_Node *node, Ripl_Node *dest, unsigned int dest_input);
int ripl_node_set(Ripl_Node *node, unsigned int param, float value);

#endif
