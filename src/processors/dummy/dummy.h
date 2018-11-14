#ifndef RIPL_DUMMY_H
#define RIPL_DUMMY_H

#include "../../audio.h"

//
// Dummy 
// a node that does nothing
//

#define RIPL_DUMMY_IN_COUNT 1
#define RIPL_DUMMY_PARAM_COUNT 1

typedef struct Ripl_Dummy {
    Ripl_Param *params[RIPL_DUMMY_PARAM_COUNT];
    float dummy;
} Ripl_Dummy;

int ripl_dummy_init(Ripl_Dummy *dummy);
int ripl_dummy_cleanup(Ripl_Dummy *dummy);
int ripl_dummy_process(void *dummy, const Ripl_Audio_Buffer **in,
                       Ripl_Audio_Buffer *out);

#endif
