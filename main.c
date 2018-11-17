#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <math.h>
#include "src/ripl.h"

#define SR 44100
#define PI    3.1415926535
#define TWOPI 6.283185

int running = 1;
Ripl_Node *osc; // TODO Ugly global
float melody[] = {RIPL_C5, RIPL_C6, RIPL_E5, RIPL_E9};

void signal_handler(int signal)
{
    if(signal == SIGINT) running = 0;
}

void callback(unsigned long long current_frame)
{
    unsigned int b = floor(((float)(current_frame % SR) / SR) * 4);
    ripl_set(osc, RIPL_OSC_FREQ, RIPL_MIDI_TO_FREQ(melody[b]));
}

int main(int arch, char **argv)
{
    signal(SIGINT, signal_handler);
    
    Ripl      *ripl = ripl_init(SR, 256, callback);
    Ripl_Node *out  = ripl_master_out(ripl);
               osc  = ripl_osc(ripl);
    
    ripl_set(osc, RIPL_OSC_FREQ, 240.0f);
    ripl_send(osc, out, 0);
    
    ripl_play(ripl);
    while(running) sleep(1);
    ripl_cleanup(ripl);
    return 0;
}
