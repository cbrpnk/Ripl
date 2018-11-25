#include <stdlib.h>
#include "node.h"
#include "graph.h"

int sndNodeInit(SndNode *node, SndNodeId id, SndGraph *owner,
                   SndProcessorType type)
{
    node->id = id;
    node->owner = owner;
    node->nInputs = 0;
    node->nOutputs = 0;
    node->inputs = NULL;
    node->outputs = NULL;
    sndProcessorInit(&node->processor, type, owner->sampleRate, owner->bufferSize);
    node->on = 1;
    return 0;
}

int sndNodeCleanup(SndNode *node)
{
    sndProcessorCleanup(&node->processor);
    if(node->nInputs > 0) free(node->inputs);
    if(node->nOutputs > 0) free(node->outputs);
    return 0;
}

int sndNodeProcess(SndNode *node)
{
    if(node->on) {
        sndProcessorProcess(&node->processor);
    }
    return 0;
}

int sndNodeSend(SndNode *node, SndNode *dest, unsigned int destInput)
{
    sndNodeAddOutput(node, dest, destInput);
    sndNodeAddInput(dest, node, destInput);
    sndProcessorSetInput(&dest->processor, destInput, &node->processor.output);
    
    // The new node connection implies an update of the signal path
    sndGraphGenSigpath(node->owner);
    return 0;
}

int sndNodeAddInput(SndNode *node, SndNode *target, unsigned int processorInput)
{
    node->inputs = realloc(node->inputs, (node->nInputs+1) * sizeof(SndEdge));
    node->inputs[node->nInputs].node = target;
    node->inputs[node->nInputs].processorInput = processorInput;
    node->nInputs++;
    return 0;
}

int sndNodeAddOutput(SndNode *node, SndNode *target, unsigned int processorInput)
{
    node->outputs = realloc(node->outputs, (node->nOutputs+1) * sizeof(SndEdge));
    node->outputs[node->nOutputs].node = target;
    node->outputs[node->nOutputs].processorInput = processorInput;
    node->nOutputs++;
    return 0;
}

int sndNodeSetParam(SndNode *node, unsigned int param, float value)
{
    sndProcessorSetParam(&node->processor, param, value);
    return 0;
}

int sndNodeOn(SndNode *node)
{
    node->on = 1;
    return 0;
}

int sndNodeOff(SndNode *node)
{
    node->on = 0;
    return 0;
}
