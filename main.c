#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <math.h>
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>

#include "src/ripl.h"

#define SR    44100
#define PI    3.1415926535
#define TWOPI 6.283185

int running = 1;
lua_State *L;
Ripl *ripl;
Ripl_Node *osc; // TODO Ugly global
Ripl_Node *out;

void signal_handler(int signal)
{
    if(signal == SIGINT) running = 0;
}

void callback(unsigned long long current_frame)
{
    lua_getglobal(L, "loop");
    lua_call(L, 0, 0);
}

/******* LUA Bindings ************/
static int ripl_lua_master_out(lua_State *L) {
    printf("I'm C, called by lua\n");
    ripl_master_out(ripl);
    lua_pushnumber(L, 12);
    return 1;
}

int main(int arch, char **argv)
{
    signal(SIGINT, signal_handler);
    ripl = ripl_init(SR, 256, callback);
    // TODO Do that in the song script
    out  = ripl_master_out(ripl);
    osc  = ripl_osc(ripl);
    ripl_send(osc, out, 0);
    
    // Init lua
    L = luaL_newstate();
    luaL_openlibs(L);
    
    // Reigster our bindings
    lua_register(L, "master_out", ripl_lua_master_out);
    
    // Load song script
    luaL_loadfile(L, "song.lua");
    lua_pcall(L, 0, 0, 0);
    
    // Call setup()
    lua_getglobal(L, "setup");
    lua_call(L, 0, 0);
    
    ripl_play(ripl);
    while(running) sleep(1); // TODO if song file changed, reload
    ripl_cleanup(ripl);
    lua_close(L);
    return 0;
}
