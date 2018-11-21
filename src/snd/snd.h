#ifndef SND_H
#define SND_H

#include "backend/backend.h"
#include "graph.h"
#include "midi.h"
#include "processors/osc.h"

#define SND_MAX_NODES 256

typedef struct Snd {
    Snd_Backend backend;
    Snd_Graph   graph;
    unsigned int playing;
    // Midi stuff
    unsigned long long play_head; // Current frame
    double time; // Current time in seconds
    double beat; // Current beat
    float bpm;
    void (*user_callback)();
    void *user_data;
} Snd;

Snd *snd_init(unsigned int sample_rate, unsigned int buffer_size,
                void(*user_callback)(void *), void *user_data);
int   snd_cleanup(Snd *snd);
int   snd_play(Snd *snd);
int   snd_stop(Snd *snd);
int   snd_callback(void *user_data, const Snd_Audio_Buffer *in, Snd_Audio_Buffer *out);

// Add nodes to graph
Snd_Node *snd_master_in(Snd *snd);
Snd_Node *snd_master_out(Snd *snd);
Snd_Node *snd_osc(Snd *snd);

// Shortcut to snd_node_send
int snd_send(Snd_Node *source, Snd_Node *dest, unsigned int dest_input);

// Shortcut to snd_node_set
int snd_set(Snd_Node *node, unsigned int param, float value);

#endif
