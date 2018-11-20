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
    lua_pushnumber(L, ripl->time);
    lua_pushnumber(L, ripl->beat);
    lua_call(L, 2, 0);
}

/******* Lua Bindings ************/
static int ripl_lua_master_out(lua_State *L) {
    Ripl_Node *out = ripl_master_out(ripl);
    lua_pushnumber(L, out->id);
    return 1;
}

static int ripl_lua_osc(lua_State *L) {
    Ripl_Node *osc = ripl_osc(ripl);
    lua_pushnumber(L, osc->id);
    return 1;
}

static int ripl_lua_send(lua_State *L) {
    Ripl_Node *source = ripl_graph_get_node(&ripl->graph, lua_tonumber(L, 1));
    Ripl_Node *target = ripl_graph_get_node(&ripl->graph, lua_tonumber(L, 2));
    unsigned int target_port = lua_tonumber(L, 3);
    ripl_send(source, target, target_port);
    return 0;
}

static int ripl_lua_set(lua_State *L) {
    Ripl_Node *node = ripl_graph_get_node(&ripl->graph, lua_tonumber(L, 1));
    ripl_set(node, lua_tonumber(L, 2), lua_tonumber(L, 3));
    return 0;
}
/********* Lua End ***************/

int main(int arch, char **argv)
{
    signal(SIGINT, signal_handler);
    ripl = ripl_init(SR, 256, callback);
    
    // Init lua
    L = luaL_newstate();
    luaL_openlibs(L);
    
    // Reigster our bindings
    lua_register(L, "master_out", ripl_lua_master_out);
    lua_register(L, "osc", ripl_lua_osc);
    lua_register(L, "send", ripl_lua_send);
    lua_register(L, "set", ripl_lua_set);
    
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
