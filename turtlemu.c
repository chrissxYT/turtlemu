#include <stdio.h>
#include <string.h>
#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"

#ifndef bool
typedef int bool;
#endif

#define TTOOL_PICKAXE 1
#define TTOOL_AXE     2
#define TTOOL_SHOVEL  3
#define TTOOL_HOE     4
#define TTOOL_SWORD   5
#define TTOOL_CTABLE  6

typedef struct
{
	int i;
	int c;
} itemstack;

typedef struct
{
	itemstack items[16];
	int       index;
} tinv;

typedef struct
{
	int x, y, z;
	int tool;
	tinv inv;
} turtle;

bool reg_func(lua_State* script, lua_CFunction function_ptr,
		     const char* function_name, const char* lib_name);

inline bool reg_func(lua_State* script, lua_CFunction function_ptr,
		     const char* function_name, const char* lib_name)
{
	if(!lib_name)
	{
		puts("lib_name is zerro!");
		return 0;
	}

	if(lib_name)
	{
		lua_getglobal(script, lib_name);
		if (lua_isnil(script, -1))
		{
			lua_pop(script, 1);
			lua_newtable(script);
			lua_pushvalue(script, -1);
			lua_setglobal(script, lib_name);
		}
	}

	lua_pushstring(script, function_name);
	lua_pushcclosure(script, function_ptr, 1);
	lua_settable(script, -3);

	lua_pop(script, 1);

	return 1;
}

turtle t;

bool ccraft(int quantity)
{
	if(t.tool != TTOOL_CTABLE) return 0;
	//craft
	return 1;
}

int craft(lua_State *L)
{
	int quantity = lua_tointeger(L, 1);
	lua_pushboolean(L, ccraft(quantity));
	return 1;
}

int main(int argc, char **argv)
{
	if(argc < 2)
	{
		puts("Usage: turtlemu [scriptfile]");
		puts("where [scriptfile] is the path");
		puts("to a computercraft compatible lua script");
		return 1;
	}
	t.x = t.y = t.z = t.inv.index = 0;
	t.tool = TTOOL_PICKAXE;
	memset(t.inv.items, 0, sizeof(itemstack) * 16);
	lua_State *L = luaL_newstate();
	luaL_openlibs(L);
	reg_func(L, craft, "craft", "turtle");
	if(luaL_loadfile(L, argv[1]) || lua_pcall(L, 0, 0, 0))
		fprintf(stderr, "Lua error: %s\n", lua_tostring(L, -1));
	lua_close(L);
	return 0;
}
