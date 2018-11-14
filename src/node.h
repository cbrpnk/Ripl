#ifndef RIPL_NODE_H
#define RIPL_NODE_H

#include "audio.h"
#include "processors/processor.h"

// Forward declaration;
typedef struct Ripl_Graph Ripl_Graph;
typedef struct Ripl_Node Ripl_Node;

typedef struct Ripl_Node {
    // Output is the first parameter so that we can cast between Ripl_Node*
    // and Ripl_Audio_Buffer*. This is useful when passing the inputs into process_func
    Ripl_Audio_Buffer output;
    Ripl_Node **input_nodes;
    Ripl_Graph *owner;
    int on;
    Ripl_Processor processor;
} Ripl_Node;

int ripl_node_init(Ripl_Node *node, Ripl_Graph *owner, Ripl_Processor_Type type);
int ripl_node_cleanup(Ripl_Node *node);

int ripl_node_process(Ripl_Node *node);
int ripl_node_send(Ripl_Node *node, Ripl_Node *dest, unsigned int dest_input);
int ripl_node_set(Ripl_Node *node, unsigned int param, float value);

#endif
