#include "luaplugins.h"


luaPlugins::luaPlugins() {}


//initializing lua:
lua_State* luaPlugins::InitLua(const QString& luaFilePath) {
    lua_State *L = luaL_newstate();
    if (!L) {
        return nullptr;

    }
    // Open Lua standard libraries
    luaL_openlibs(L);

    // Load and execute the Lua file
    if (luaL_dofile(L, luaFilePath.toUtf8().constData()) != LUA_OK) {
        lua_close(L);
        return nullptr;
    }
    //qDebug() << "lua is succefully initialized ! " ;
    return L;
}
