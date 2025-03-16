#ifndef LUAPLUGINS_H
#define LUAPLUGINS_H

#include <lua.hpp>
#include<QString>
#include <QDebug>


class luaPlugins
{

public:
    luaPlugins();
    lua_State* InitLua(const QString& luaFilePath);
    void LuaFormatText();
};



#endif // LUAPLUGINS_H
