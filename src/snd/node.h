#ifndef SND_NODE_H
#define SND_NODE_H
#include "processors/processor.h"

// Forward declaration;
typedef struct SndGraph SndGraph;
typedef struct SndNode SndNode;

// Unique identifier to a node
typedef unsigned int SndNodeId;

typedef struct SndEdge {
    SndNode *node;
    unsigned int processorInput;
} SndEdge;

// Represents a single node in a SndGraph
typedef struct SndNode {
    SndNodeId id;
    SndGraph *owner;
    unsigned int nInputs;
    unsigned int nOutputs;
    SndEdge *inputs;
    SndEdge *outputs;
    SndProcessor processor;
    int on;
} SndNode;

int sndNodeInit(SndNode *node, SndNodeId id, SndGraph *owner,
                   SndProcessorType type);
int sndNodeCleanup(SndNode *node);

int sndNodeProcess(SndNode *node);
int sndNodeSend(SndNode *node, SndNode *dest, unsigned int destInput);
int sndNodeAddInput(SndNode *node, SndNode *target, unsigned int processorInput);
int sndNodeAddOutput(SndNode *node, SndNode *target, unsigned int processorInput);
int sndNodeSetParam(SndNode *node, unsigned int param, float value);

int sndNodeOn(SndNode *node);
int sndNodeOff(SndNode *node);

#endif
