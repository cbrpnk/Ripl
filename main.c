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
    
    Ripl *ripl = ripl_init(44100, 256);
    Ripl_Synth *synth = ripl_add_synth(ripl);
    
    synth->freq = 120.0f;
    
    ripl_play(ripl, synth->node);
    while(running) sleep(1);
    ripl_cleanup(ripl);
    return 0;
}
