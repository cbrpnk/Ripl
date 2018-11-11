#ifndef RIPL_NODE_H
#define RIPL_NODE_H

#include "../audio.h"

typedef enum Ripl_Node_Type {
    RIPL_SYNTH = 0
} Ripl_Node_Type;


// Forward declaration;
typedef struct Ripl_Node Ripl_Node;

typedef struct Ripl_Node {
    Ripl_Node_Type type;
    void *params;
    int (*process_func)(void*, const Ripl_Audio_Buffer*, Ripl_Audio_Buffer*);
    Ripl_Node *input;
    Ripl_Audio_Buffer output_buffer;
    int on;
} Ripl_Node;

int ripl_node_init(Ripl_Node *node, Ripl_Node_Type type, unsigned int sample_rate,
                     unsigned int buffer_size,
                     int (process_func)(void*, const Ripl_Audio_Buffer*,
                                        Ripl_Audio_Buffer*));
int ripl_node_cleanup(Ripl_Node *node);

#endif
