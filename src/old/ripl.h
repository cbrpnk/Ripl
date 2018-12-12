#ifndef RIPL_H
#define RIPL_H

typedef struct Snd Snd;
typedef struct lua_State lua_State;

typedef struct Ripl {
    Snd *snd;
    lua_State *lua;
    unsigned int running;
} Ripl;

#endif
