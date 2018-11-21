#ifndef LUA_BINDINGS_H
#define LUA_BINDINGS_H

#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
#include "snd/snd.h"
#include "ripl.h"

static int snd_lua_master_out(lua_State *L)
{
    lua_getglobal(L, "snd");
    lua_pushlightuserdata(L, snd_master_out(lua_touserdata(L, 1)));
    return 1;
}

static int snd_lua_osc(lua_State *L)
{
    lua_getglobal(L, "snd");
    lua_pushlightuserdata(L, snd_osc(lua_touserdata(L, 1)));
    return 1;
}

static int snd_lua_send(lua_State *L)
{
    snd_send(lua_touserdata(L, 1), lua_touserdata(L, 2), lua_tonumber(L, 3));
    return 0;
}

static int snd_lua_set(lua_State *L)
{
    snd_set(lua_touserdata(L, 1), lua_tonumber(L, 2), lua_tonumber(L, 3));
    return 0;
}

void snd_lua_register_bindings(Ripl *ripl)
{
    lua_register(ripl->lua, "masterOut", snd_lua_master_out);
    lua_register(ripl->lua, "osc", snd_lua_osc);
    lua_register(ripl->lua, "send", snd_lua_send);
    lua_register(ripl->lua, "set", snd_lua_set);
}
#endif
