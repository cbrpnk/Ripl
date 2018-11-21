#ifndef SND_AUDIO_H
#define SND_AUDIO_H


typedef float Snd_Param;

typedef struct __attribute__((packed)) Snd_Audio_Frame {
    float left;
    float right;
} Snd_Audio_Frame;

typedef struct Snd_Audio_Buffer {
    unsigned int size; // TODO size_t ?
    Snd_Audio_Frame *buffer;
} Snd_Audio_Buffer;


#endif
