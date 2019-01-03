#include <stdio.h>
#include <string.h>
#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"

int main(int argc, char **argv)
{
	if(argc < 2)
	{
		puts("Usage: turtlemu [scriptfile]");
		puts("where [scriptfile] is replaced with the path");
		puts("to a turtle lua script");
		return 1;
	}
	lua_State *L = luaL_newstate();
	luaL_openlibs(L);
	lua_pushcfunction(L, foo);
	lua_setglobal(L, "foo");
	if(luaL_loadfile(L, argv[1]) || lua_pcall(L, 0, 0, 0))
	{
		printf("Lua error: %s\n", lua_tostring(L, -1));
	}
	lua_close(L);
	return 0;
}
