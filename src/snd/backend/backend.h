#ifndef SND_BACKEND_H
#define SND_BACKEND_H

#include <portaudio.h>
#include "../audio.h"

typedef struct Snd_Backend {
    PaStream* stream;
    int (*user_callback)(void *, const Snd_Audio_Buffer*, Snd_Audio_Buffer*);
    void* user_data;
} Snd_Backend;

int snd_backend_init(Snd_Backend *backend,
                      int (*user_callback)(void *, const Snd_Audio_Buffer*,
                      Snd_Audio_Buffer*), void *user_data);
int snd_backend_cleanup(Snd_Backend *backend);
int snd_backend_open_device(Snd_Backend *backend, unsigned int sample_rate,
                      unsigned int buffer_size);
int snd_backend_close_device(Snd_Backend *backend);
int snd_backend_callback(const void *input_buffer, void *output_buffer,
                          unsigned long n_frames, const PaStreamCallbackTimeInfo *time_info,
                          PaStreamCallbackFlags status_flags, void *user_data);

#endif
