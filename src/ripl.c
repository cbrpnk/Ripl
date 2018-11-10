#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "ripl.h"
#include "audio.h"

Ripl *ripl_init(unsigned int sample_rate, unsigned int buffer_size)
{
    srand(time(NULL));
    
    Ripl *ripl = (Ripl*) malloc(sizeof(Ripl));
    ripl->playing = 0;
    ripl->sample_rate = sample_rate;
    ripl->buffer_size = buffer_size;
    ripl->n_modules = 0;
    
    ripl_backend_init(&ripl->backend, ripl_callback, (void *) ripl);
    ripl_backend_open_device(&ripl->backend, ripl->sample_rate, ripl->buffer_size);
    return ripl;
}

int ripl_cleanup(Ripl *ripl)
{
    ripl_stop(ripl);
    ripl_backend_close_device(&ripl->backend);
    ripl_backend_cleanup(&ripl->backend);
    
    for(int i=0; i<ripl->n_modules; ++i) {
        ripl_module_cleanup(ripl->modules[i]);
        free(ripl->modules[i]);
    }
    
    free(ripl);
    return 0;
}

int ripl_play(Ripl *ripl, Ripl_Module *module)
{
    ripl->output_module = module;
    ripl->playing = 1;
    return 0;
}

int ripl_stop(Ripl *ripl)
{
    ripl->playing = 0;
    return 0;
}

int ripl_callback(const void *in, void *out, unsigned long n_frames, void *user_data)
{
    Ripl *ripl = (Ripl *) user_data;
    Ripl_Audio_Buffer in_buffer = {.size = n_frames, .buffer = (Ripl_Audio_Frame *) in};
    Ripl_Audio_Buffer out_buffer = {.size = n_frames, .buffer = (Ripl_Audio_Frame *) out};
    
    // Silence buffer
    memset(out_buffer.buffer, 0, sizeof(Ripl_Audio_Frame) * n_frames);
    
    if(ripl->playing) {
        // TODO Check if there is an output_module to ripl
        
        // Build Execution stack
        Ripl_Module *stack[100]; // TODO find something better than to hardcode 100
        unsigned int stack_size = 0;
        
        stack[stack_size] = ripl->output_module;
        ++stack_size;
        Ripl_Module *parent = stack[stack_size]->input;
        while(parent) {
            stack[stack_size] = parent;
            ++stack_size;
            parent = stack[stack_size]->input;
        }
        
        // Execute Stack
        Ripl_Audio_Buffer *in_ptr = &in_buffer;
        for(int i=0; i<stack_size; ++i) {
            // TODO The input buffer should be the output buffer of the previous 
            // module if there was one or in_buffer if it's the first in the stack.

            if(i > 0) {
                // If this is not the first module we want the input to be the previous
                // modules output
                in_ptr = &(stack[i-1]->output_buffer);
            } 
            
            stack[i]->process_func(stack[i]->params, &in_buffer,
                                   &(stack[i]->output_buffer));
        }
        
        // Copy output node into soundcard buffer
        memcpy(out_buffer.buffer, ripl->output_module->output_buffer.buffer,
               n_frames * sizeof(Ripl_Audio_Frame));
    }
    return 0;
}

Ripl_Synth *ripl_add_synth(Ripl *ripl)
{
    Ripl_Module *module = (Ripl_Module *) malloc(sizeof(Ripl_Module));
    ripl->modules[ripl->n_modules++] = module;
    ripl_module_init(module, RIPL_SYNTH,  ripl->sample_rate,
                     ripl->buffer_size, ripl_synth_process);
    return (Ripl_Synth *) module->params;
}
