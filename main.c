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
    
    Ripl      *ripl = ripl_init(44100, 256);
    Ripl_Node *out  = ripl_master_out(ripl);
    Ripl_Node *osc  = ripl_osc(ripl);
    
    ripl_set(osc, RIPL_OSC_FREQ, 240.0f);
    ripl_send(osc, out, 0);
    
    ripl_play(ripl);
    while(running) sleep(1);
    ripl_cleanup(ripl);
    return 0;
}
