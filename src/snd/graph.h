#ifndef SND_GRAPH_H
#define SND_GRAPH_H

#include "node.h"

#define SND_MAX_NODES 256

//
// SndGraph
// Manages SndNodes and computes the signal that goes through them
//
typedef struct SndGraph {
    unsigned int sampleRate;
    unsigned int bufferSize;
    // All the nodes we manage
    unsigned int nNodes;
    SndNode *nodes[SND_MAX_NODES];
    // Ordered nodes that should be processed when calling sndGraphProcess
    unsigned int signalPathLength;
    SndNode *signalPath[SND_MAX_NODES];
    // Where the signal graph touches the external world
    SndNode *masterIn;
    SndNode *masterOut;
} SndGraph;

int sndGraphInit(SndGraph *graph, unsigned int sampleRate, unsigned int bufferSize);
// TODO Reset should be passed sample rate and buffer size, init should only allocate mem
int sndGraphReset(SndGraph *graph);
int sndGraphCleanup(SndGraph *graph);

// Put the nodes in the order they should be executed in
int sndGraphGenSigpath(SndGraph *graph);
int sndGraphGenSigpathRecursive(SndGraph *graph, SndNode *root);

// Goes through the graph and execute the nodes.
int sndGraphProcess(SndGraph *graph, const SndAudioBuffer *in,
                       SndAudioBuffer *out);

// Add nodes
SndNode *sndGraphAdd(SndGraph *graph, SndProcessorType type);

// Get node by id
SndNode *sndGraphGetNode(SndGraph *graph, SndNodeId id);

#endif
