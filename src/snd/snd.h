#ifndef SND_H
#define SND_H

#include "backend/backend.h"
#include "graph.h"
#include "midi.h"
#include "processors/osc.h"

#define SND_MAX_NODES 256

typedef struct Snd {
    SndBackend backend;
    SndGraph   graph;
    unsigned int playing;
    // Midi stuff
    unsigned long long playHead; // Current frame
    double time; // Current time in seconds
    double beat; // Current beat
    float bpm;
    void (*userCallback)();
    void *userData;
} Snd;

Snd *sndInit(unsigned int sampleRate, unsigned int bufferSize,
                void(*userCallback)(void *), void *userData);
int  sndCleanup(Snd *snd);
int  sndPlay(Snd *snd);
int  sndStop(Snd *snd);
int  sndCallback(void *userData, const SndAudioBuffer *in, SndAudioBuffer *out);

// Add nodes to graph
SndNode *sndMasterIn(Snd *snd);
SndNode *sndMasterOut(Snd *snd);
SndNode *sndOsc(Snd *snd);

// Reset Graph
int sndResetGraph(Snd *snd);

// Shortcut to sndNodeSend
int sndSend(SndNode *source, SndNode *dest, unsigned int destInput);

// Shortcut to sndNodeSet
int sndSet(SndNode *node, unsigned int param, float value);

#endif
