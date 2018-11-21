#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <math.h>
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>

#include "state.h"
#include "src/ripl.h"
#include "lua_ripl_bindings.h"

State state;

void signal_handler(int signal)
{
    if(signal == SIGINT) {
        // Cleanup and exit
        ripl_cleanup(state.ripl);
        lua_close(state.lua);
        exit(0);
    }
}

void callback(void *data)
{
    State *state = (State *) data;
    lua_getglobal(state->lua, "loop");
    lua_pushnumber(state->lua, state->ripl->time);
    lua_pushnumber(state->lua, state->ripl->beat);
    lua_call(state->lua, 2, 0);
}

int main(int arch, char **argv)
{
    signal(SIGINT, signal_handler);
    state.ripl = ripl_init(44100, 256, callback, &state);
    state.lua = luaL_newstate();
    luaL_openlibs(state.lua);
    state.running = 1;
    
    // Push Ripl state into Lua state
    lua_pushlightuserdata(state.lua, state.ripl);
    lua_setglobal(state.lua, "ripl");
    
    // Reigster our bindings
    ripl_lua_register_bindings(&state);
    
    // Load song script
    luaL_loadfile(state.lua, "song.lua");
    lua_pcall(state.lua, 0, 0, 0);
    
    // Call setup()
    lua_getglobal(state.lua, "setup");
    lua_call(state.lua, 0, 0);
    
    ripl_play(state.ripl);
    while(state.running) sleep(1); // TODO if song file changed, reload
    return 0;
}
