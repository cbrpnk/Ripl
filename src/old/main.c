#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <signal.h>
#include <math.h>
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>

#include "ripl.h"
#include "snd/snd.h"
#include "lua_snd_bindings.h"

unsigned int running = 1;

void signalHandler(int signal)
{
    if(signal == SIGINT) running = 0;
}

void callback(void *data)
{
    Ripl *ripl = (Ripl *) data;
    lua_getglobal(ripl->lua, "loop");
    lua_pushnumber(ripl->lua, ripl->snd->time);
    lua_pushnumber(ripl->lua, ripl->snd->beat);
    lua_call(ripl->lua, 2, 0);
}

void loadScript(Ripl *ripl, char *path)
{
    ripl->lua = luaL_newstate();
    luaL_openlibs(ripl->lua);
    
    // Push Snd state into Lua state
    lua_pushlightuserdata(ripl->lua, ripl->snd);
    lua_setglobal(ripl->lua, "snd");

    // Reigster our bindings
    sndLuaRegisterBindings(ripl);

    // Load lua script passed as parameter
    luaL_loadfile(ripl->lua, path);
    lua_pcall(ripl->lua, 0, 0, 0);

    // Call setup()
    lua_getglobal(ripl->lua, "setup");
    lua_call(ripl->lua, 0, 0);
}

// TODO Snd have the ability to reset the Snd graph
int main(int argc, char **argv)
{
    if(argc == 2) {
        signal(SIGINT, signalHandler);
        Ripl ripl;
        // Put this in an init function
        ripl.snd = sndInit(44100, 256, callback, &ripl);
        ripl.lua = luaL_newstate();
        
        time_t lastReload = 0;
        while(running) {
            struct stat result;
            if(stat(argv[1], &result) == 0) {
                time_t lastMod = result.st_mtime;
                
                if(lastMod > lastReload) {
                    sndStop(ripl.snd);
                    sndResetGraph(ripl.snd);
                    lua_close(ripl.lua);
                    loadScript(&ripl, argv[1]);
                    sndPlay(ripl.snd);
                    lastReload = lastMod;
                }
            }
            sleep(1);
        }
        
        // Cleanup
        sndCleanup(ripl.snd);
        lua_close(ripl.lua);
    }
    return 0;
}
