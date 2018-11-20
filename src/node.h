#ifndef RIPL_NODE_H
#define RIPL_NODE_H

#include "processors/processor.h"

// Forward declaration;
typedef struct Ripl_Graph Ripl_Graph;
typedef struct Ripl_Node Ripl_Node;

// Unique identifier to a node
typedef unsigned int Ripl_Node_Id;

typedef struct Ripl_Edge {
    Ripl_Node *node;
    unsigned int processor_input;
} Ripl_Edge;

// Represents a single node in a Ripl_Graph
typedef struct Ripl_Node {
    Ripl_Node_Id id;
    Ripl_Graph *owner;
    unsigned int n_inputs;
    unsigned int n_outputs;
    Ripl_Edge *inputs;
    Ripl_Edge *outputs;
    Ripl_Processor processor;
    int on;
} Ripl_Node;

int ripl_node_init(Ripl_Node *node, Ripl_Node_Id id, Ripl_Graph *owner,
                   Ripl_Processor_Type type);
int ripl_node_cleanup(Ripl_Node *node);

int ripl_node_process(Ripl_Node *node);
int ripl_node_send(Ripl_Node *node, Ripl_Node *dest, unsigned int dest_input);
int ripl_node_add_input(Ripl_Node *node, Ripl_Node *target, unsigned int processor_input);
int ripl_node_add_output(Ripl_Node *node, Ripl_Node *target, unsigned int processor_input);
int ripl_node_set_param(Ripl_Node *node, unsigned int param, float value);

int ripl_node_on(Ripl_Node *node);
int ripl_node_off(Ripl_Node *node);

#endif
