#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <math.h>
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>

#include "ripl.h"
#include "snd/snd.h"
#include "lua_snd_bindings.h"

Ripl ripl;

void signal_handler(int signal)
{
    if(signal == SIGINT) {
        // Cleanup and exit
        snd_cleanup(ripl.snd);
        lua_close(ripl.lua);
        exit(0);
    }
}

void callback(void *data)
{
    Ripl *ripl = (Ripl *) data;
    lua_getglobal(ripl->lua, "loop");
    lua_pushnumber(ripl->lua, ripl->snd->time);
    lua_pushnumber(ripl->lua, ripl->snd->beat);
    lua_call(ripl->lua, 2, 0);
}

int main(int argc, char **argv)
{
    if(argc == 2) {
        signal(SIGINT, signal_handler);
        ripl.snd = snd_init(44100, 256, callback, &ripl);
        ripl.lua = luaL_newstate();
        luaL_openlibs(ripl.lua);
        ripl.running = 1;

        // Push Snd state into Lua state
        lua_pushlightuserdata(ripl.lua, ripl.snd);
        lua_setglobal(ripl.lua, "snd");

        // Reigster our bindings
        snd_lua_register_bindings(&ripl);

        // Load lua script passed as parameter
        luaL_loadfile(ripl.lua, argv[1]);
        lua_pcall(ripl.lua, 0, 0, 0);

        // Call setup()
        lua_getglobal(ripl.lua, "setup");
        lua_call(ripl.lua, 0, 0);

        snd_play(ripl.snd);
        while(ripl.running) sleep(1); // TODO if song script changed, reload
    }
    return 0;
}
