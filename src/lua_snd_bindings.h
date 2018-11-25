#ifndef LUA_BINDINGS_H
#define LUA_BINDINGS_H

#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
#include "snd/snd.h"
#include "ripl.h"

static int sndLuaMasterOut(lua_State *L)
{
    lua_getglobal(L, "snd");
    lua_pushlightuserdata(L, sndMasterOut(lua_touserdata(L, 1)));
    return 1;
}

static int sndLuaOsc(lua_State *L)
{
    lua_getglobal(L, "snd");
    lua_pushlightuserdata(L, sndOsc(lua_touserdata(L, 1)));
    return 1;
}

static int sndLuaSend(lua_State *L)
{
    sndSend(lua_touserdata(L, 1), lua_touserdata(L, 2), lua_tonumber(L, 3));
    return 0;
}

static int sndLuaSet(lua_State *L)
{
    sndSet(lua_touserdata(L, 1), lua_tonumber(L, 2), lua_tonumber(L, 3));
    return 0;
}

void sndLuaRegisterBindings(Ripl *ripl)
{
    lua_register(ripl->lua, "masterOut", sndLuaMasterOut);
    lua_register(ripl->lua, "osc", sndLuaOsc);
    lua_register(ripl->lua, "send", sndLuaSend);
    lua_register(ripl->lua, "set", sndLuaSet);
}
#endif
