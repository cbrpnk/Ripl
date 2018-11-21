#ifndef SND_PROCESSOR_MIXER_H
#define SND_PROCESSOR_MIXER_H


typedef struct Snd_Processor Snd_Processor;

typedef enum Snd_Processor_Mixer_Param {
    SND_MIXER_MASTER_LVL = 0,
    SND_MIXER_PARAM_COUNT
} Snd_Processor_Mixer_Param;

int snd_processor_mixer_init(Snd_Processor *processor, unsigned int sample_rate);


#endif
