#ifndef RIPL_AUDIO_H
#define RIPL_AUDIO_H

typedef struct __attribute__((packed)) Ripl_Audio_Frame {
    float left;
    float right;
} Ripl_Audio_Frame;

typedef struct Ripl_Audio_Buffer {
    unsigned int size; // TODO size_t ?
    Ripl_Audio_Frame *buffer;
} Ripl_Audio_Buffer;


#endif
