#ifndef SND_NODE_H
#define SND_NODE_H
#include "processors/processor.h"

// Forward declaration;
typedef struct Snd_Graph Snd_Graph;
typedef struct Snd_Node Snd_Node;

// Unique identifier to a node
typedef unsigned int Snd_Node_Id;

typedef struct Snd_Edge {
    Snd_Node *node;
    unsigned int processor_input;
} Snd_Edge;

// Represents a single node in a Snd_Graph
typedef struct Snd_Node {
    Snd_Node_Id id;
    Snd_Graph *owner;
    unsigned int n_inputs;
    unsigned int n_outputs;
    Snd_Edge *inputs;
    Snd_Edge *outputs;
    Snd_Processor processor;
    int on;
} Snd_Node;

int snd_node_init(Snd_Node *node, Snd_Node_Id id, Snd_Graph *owner,
                   Snd_Processor_Type type);
int snd_node_cleanup(Snd_Node *node);

int snd_node_process(Snd_Node *node);
int snd_node_send(Snd_Node *node, Snd_Node *dest, unsigned int dest_input);
int snd_node_add_input(Snd_Node *node, Snd_Node *target, unsigned int processor_input);
int snd_node_add_output(Snd_Node *node, Snd_Node *target, unsigned int processor_input);
int snd_node_set_param(Snd_Node *node, unsigned int param, float value);

int snd_node_on(Snd_Node *node);
int snd_node_off(Snd_Node *node);

#endif
