#include <iostream>
#include <unistd.h>

extern "C" {
    #include "snd/snd.h"
}

int main(int argc, char** argv)
{
    Snd* snd = sndInit(44100, 256, NULL, NULL);
    SndNode* masterOut = sndMasterOut(snd);
    
    SndNode* osc = sndOsc(snd);
    sndSet(osc, SND_OSC_FREQ, 60);
    sndSend(osc, masterOut, 0);
    
    Snd* sndInit(44100, 256, NULL, NULL);
    SndId osc = sndDo(snd, SND_NEW, SND_OSC);
    sndDo(snd, SND_SET, SND_OSC_FREQ, 60);
    sndDo(snd, SND_SEND, osc, mixer, 0);
    
    sndDo(Snd *snd, SndAction action, float arg1, float arg2, float arg3);
    
    sndPlay(snd);
    while(1) {
        sleep(1);
    }
    
    std::cout << "Hello Ripl\n";
    return 0;
}
