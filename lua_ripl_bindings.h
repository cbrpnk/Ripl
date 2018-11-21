#ifndef LUA_BINDINGS_H
#define LUA_BINDINGS_H

#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
#include "src/ripl.h"
#include "state.h"

static int ripl_lua_master_out(lua_State *L)
{
    lua_getglobal(L, "ripl");
    lua_pushlightuserdata(L, ripl_master_out(lua_touserdata(L, 1)));
    return 1;
}

static int ripl_lua_osc(lua_State *L)
{
    lua_getglobal(L, "ripl");
    lua_pushlightuserdata(L, ripl_osc(lua_touserdata(L, 1)));
    return 1;
}

static int ripl_lua_send(lua_State *L)
{
    ripl_send(lua_touserdata(L, 1), lua_touserdata(L, 2), lua_tonumber(L, 3));
    return 0;
}

static int ripl_lua_set(lua_State *L)
{
    ripl_set(lua_touserdata(L, 1), lua_tonumber(L, 2), lua_tonumber(L, 3));
    return 0;
}

void ripl_lua_register_bindings(State *state)
{
    lua_register(state->lua, "masterOut", ripl_lua_master_out);
    lua_register(state->lua, "osc", ripl_lua_osc);
    lua_register(state->lua, "send", ripl_lua_send);
    lua_register(state->lua, "set", ripl_lua_set);
}
#endif
