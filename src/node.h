#ifndef RIPL_NODE_H
#define RIPL_NODE_H

#include "processors/processor.h"

// Forward declaration;
typedef struct Ripl_Graph Ripl_Graph;
typedef struct Ripl_Node Ripl_Node;

// Represents a single node in a Ripl_Graph
typedef struct Ripl_Node {
    Ripl_Graph *owner;
    // Fixed length array of inputs in the same order than the processor inputs
    Ripl_Node **inputs;
    Ripl_Node **outputs;
    Ripl_Processor processor;
    int on;
} Ripl_Node;

int ripl_node_init(Ripl_Node *node, Ripl_Graph *owner, Ripl_Processor_Type type);
int ripl_node_cleanup(Ripl_Node *node);

int ripl_node_process(Ripl_Node *node);
int ripl_node_send(Ripl_Node *node, Ripl_Node *dest, unsigned int dest_input);
int ripl_node_set(Ripl_Node *node, unsigned int param, float value);

#endif
