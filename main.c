#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include "src/ripl.h"

int running = 1;

void signal_handler(int signal)
{
    if(signal == SIGINT) running = 0;
}

int main(int arch, char **argv)
{
    signal(SIGINT, signal_handler);
    
    Ripl *ripl = ripl_init(44100, 256);         // Sampling rate, buffer size
    Ripl_Mixer *mixer = &ripl->mixer;
    Ripl_Synth *synth = ripl_synth_init(ripl);
    // Ripl_Synth *synth = ripl_add_synth(ripl, 0); // TODO make ripl manage modules
    
    synth->dummy = 1;
    
    ripl_add(ripl, synth, 0);
    ripl_play(ripl);
    
    
    while(running) sleep(1);
    ripl_synth_cleanup(synth);
    ripl_cleanup(ripl);
    return 0;
}
