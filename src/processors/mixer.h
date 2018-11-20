#ifndef RIPL_PROCESSOR_MIXER_H
#define RIPL_PROCESSOR_MIXER_H


typedef struct Ripl_Processor Ripl_Processor;

typedef enum Ripl_Processor_Mixer_Param {
    RIPL_MIXER_MASTER_LVL = 0,
    RIPL_MIXER_PARAM_COUNT
} Ripl_Processor_Mixer_Param;

int ripl_processor_mixer_init(Ripl_Processor *processor, unsigned int sample_rate);


#endif
