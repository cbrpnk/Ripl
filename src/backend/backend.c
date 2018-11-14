#include <stdio.h>
#include "backend.h"

int ripl_backend_init(Ripl_Backend *backend,
                      int (*user_callback)(void *, const Ripl_Audio_Buffer*,
                      Ripl_Audio_Buffer*),
                      void *user_data)
{
    PaError err = Pa_Initialize();
    if(err != paNoError) {
        printf("ripl_backend_init() error: %s\n", Pa_GetErrorText(err));
        return 1;
    }
    
    backend->user_callback = user_callback;
    backend->user_data = user_data;
    
    return 0;
}

int ripl_backend_cleanup(Ripl_Backend *backend)
{
    PaError err = Pa_Terminate();
    if(err != paNoError) {
        printf("ripl_backend_cleanup error: %s\n", Pa_GetErrorText(err));
        return 1;
    }
    return 0;
}

int ripl_backend_open_device(Ripl_Backend *backend, unsigned int sample_rate,
                             unsigned int buffer_size)
{
    PaError err;
    
    err = Pa_OpenDefaultStream(&backend->stream, 0, 2, paFloat32, sample_rate,
                               buffer_size, ripl_backend_callback, backend);
    if(err != paNoError) {
        printf("ripl_backend_open_device error: %s\n", Pa_GetErrorText(err));
        return 1;
    }
    
    err = Pa_StartStream(backend->stream);
    if(err != paNoError) {
        printf("ripl_backend_open_device error: %s\n", Pa_GetErrorText(err));
        return 1;
    }
    return 0;
}

int ripl_backend_close_device(Ripl_Backend *backend)
{
    Pa_StopStream(backend->stream);
    Pa_CloseStream(backend->stream);
}

int ripl_backend_callback(const void *input_buffer, void *output_buffer,
                          unsigned long n_frames, const PaStreamCallbackTimeInfo *time_info,
                          PaStreamCallbackFlags status_flags, void *user_data)
{
    Ripl_Backend *backend = (Ripl_Backend *) user_data;
    Ripl_Audio_Buffer in = {
        .size = n_frames,
        .buffer = (Ripl_Audio_Frame *) input_buffer
    };
    Ripl_Audio_Buffer out = {
        .size = n_frames,
        .buffer = (Ripl_Audio_Frame *) output_buffer
    };
    
    return backend->user_callback(backend->user_data, (const Ripl_Audio_Buffer*) &in, &out);
}
