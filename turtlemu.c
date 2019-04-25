#include <stdio.h>
#include <string.h>
#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"

#define TTOOL_PICKAXE 1

typedef struct
{
	int i;
	int c;
} itemstack;

typedef struct
{
	int x, y, z;
	int tool;
	itemstack inv[16];
} turtle;

turtle t;

int main(int argc, char **argv)
{
	if(argc < 2)
	{
		puts("Usage: turtlemu [scriptfile]");
		puts("where [scriptfile] is the path");
		puts("to a computercraft compatible lua script");
		return 1;
	}
	t.x = t.y = t.z = 0;
	t.tool = TTOOL_PICKAXE;
	memset(t.inv, 0, sizeof(itemstack) * 16);
	lua_State *L = luaL_newstate();
	luaL_openlibs(L);
	lua_pushcfunction(L, foo);
	lua_setglobal(L, "foo");
	if(luaL_loadfile(L, argv[1]) || lua_pcall(L, 0, 0, 0))
		printf("Lua error: %s\n", lua_tostring(L, -1));
	lua_close(L);
	return 0;
}
