#ifndef SND_AUDIO_H
#define SND_AUDIO_H


typedef float SndParam;

typedef struct __attribute__((packed)) SndAudioFrame {
    float left;
    float right;
} SndAudioFrame;

typedef struct SndAudioBuffer {
    unsigned int size; // TODO size_t ?
    SndAudioFrame *buffer;
} SndAudioBuffer;


#endif
