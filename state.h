#ifndef STATE_H
#define STATE_H

typedef struct Ripl Ripl;
typedef struct lua_State lua_State;

typedef struct State {
    Ripl *ripl;
    lua_State *lua;
    unsigned int running;
} State;

#endif
