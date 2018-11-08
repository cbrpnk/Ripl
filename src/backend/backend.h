#ifndef RIPL_BACKEND_H
#define RIPL_BACKEND_H

#include <portaudio.h>

typedef struct Ripl_Backend {
    PaStream* stream;
    int (*user_callback)(const void*, void*, unsigned long, void*);
    void* user_data;
} Ripl_Backend;

int ripl_backend_init(Ripl_Backend *backend,
                      int (*user_callback)(const void*, void*, unsigned long, void*),
                      void *user_data);
int ripl_backend_cleanup(Ripl_Backend *backend);
int ripl_backend_open_device(Ripl_Backend *backend, unsigned int sample_rate,
                      unsigned int buffer_size);
int ripl_backend_close_device(Ripl_Backend *backend);
int ripl_backend_callback(const void *input_buffer, void *output_buffer,
                          unsigned long frame_per_puffer,
                          const PaStreamCallbackTimeInfo *time_info,
                          PaStreamCallbackFlags status_flags, void *user_data);

#endif
