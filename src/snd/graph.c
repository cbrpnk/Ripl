#include <stdlib.h>
#include <string.h>
#include "graph.h"

int sndGraphInit(SndGraph *graph, unsigned int sampleRate, unsigned int bufferSize)
{
    graph->sampleRate = sampleRate;
    graph->bufferSize = bufferSize;
    graph->nNodes = 0;
    graph->signalPathLength = 0;
    graph->masterIn = sndGraphAdd(graph, SND_DUMMY);
    graph->masterOut = sndGraphAdd(graph, SND_DUMMY);
    return 0;
}

// TODO Reset should be passed sample rate and buffer size, init should only allocate mem
int sndGraphReset(SndGraph *graph)
{
    sndGraphCleanup(graph);
    sndGraphInit(graph, graph->sampleRate, graph->bufferSize);
    return 0;
}

int sndGraphCleanup(SndGraph *graph)
{
    for(int i=0; i<graph->nNodes; ++i) {
        sndNodeCleanup(graph->nodes[i]);
        free(graph->nodes[i]);
    }
    return 0;
}

int sndGraphGenSigpath(SndGraph *graph)
{
    sndGraphGenSigpathRecursive(graph, graph->masterOut);
    return 0;
}

int sndGraphGenSigpathRecursive(SndGraph *graph, SndNode *root)
{
    // Recusively go through the graph and build a signal path in a depth first fashion
    for(int i=0; i<root->nInputs; ++i) {
        // Search node in path
        unsigned int inPath = 0;
        for(int j=0; j<graph->signalPathLength; ++j) {
            if(root->inputs[i].node == graph->signalPath[j]) {
                inPath = 1;
                break;
            }
        }
        
        if(!inPath) {
            sndGraphGenSigpathRecursive(graph, root->inputs[i].node);
        }
    }
    
    // We went through all out inputs, add ourself to the signal path
    graph->signalPath[graph->signalPathLength] = root;
    graph->signalPathLength++;
    return 0;
}

int sndGraphProcess(SndGraph *graph, const SndAudioBuffer *in,
                       SndAudioBuffer *out)
{
    // TODO Set masterIn to in

    for(int i=0; i<graph->signalPathLength; ++i) {
        sndNodeProcess(graph->signalPath[i]);
    }
    
    // Copy the output buffer of the node connected to master out into out
    if(graph->masterOut->nInputs > 0) {
        memcpy(out->buffer, graph->masterOut->inputs[0].node->processor.output.buffer,
               out->size * sizeof(SndAudioFrame));
    }
    return 0;
}

SndNode *sndGraphAdd(SndGraph *graph, SndProcessorType type)
{
    SndNode *node = malloc(sizeof(SndNode));
    graph->nodes[graph->nNodes] = node;
    sndNodeInit(node, graph->nNodes, graph, type);
    graph->nNodes++;
    return node;
}

SndNode *sndGraphGetNode(SndGraph *graph, SndNodeId id)
{
    if(id < graph->nNodes) {
        return graph->nodes[id];
    }
    return NULL;
}
