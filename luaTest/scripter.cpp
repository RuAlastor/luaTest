#include "scripter.h"


using namespace Sorokin;

/* Methods setting the Scripter obj up */
Scripter::Scripter() noexcept(false) {
    _script = luaL_newstate();
    if (_script == NULL) { // Error if unable to allocate memory
        throw 0;
    }
}
int Scripter::setScriptFile(const char *scriptFileName) noexcept {
    if (luaL_loadfile(_script, scriptFileName) != LUA_OK) {
        return -1;
    }
    return 0;
}
int Scripter::runScript() noexcept {
    if (lua_pcall(_script, 0, 0, 0) != LUA_OK) {
        const char* luaError = lua_tostring(_script, -1);
        std::cout << "Failed to run script!\n" << luaError << '\n';
        return -1;
    }
    return 0;
}

/* Running specific functions of script file */
int Scripter::modifyCharArray(const std::string &toModify, std::string &modified) noexcept(false) {
    const char* luaFuncName = "reverse";

    lua_getglobal(_script, luaFuncName);
    if (lua_pushstring(_script, toModify.c_str()) == NULL) { // Possible error
        std::cout << "Failed to push to stack!\n";
        return -1;
    }
    if (lua_pcall(_script, 1, 1, 0) != LUA_OK) { // Possible error
        const char* luaError = lua_tostring(_script, -1);
        std::cout << "Failed to run script!\n" << luaError << '\n';
        return -1;
    }

    modified.clear();
    modified = lua_tostring(_script, -1);
    lua_pop(_script, 1);

    return 0;
}
int Scripter::sumTwo(int &x, int &y, int &answer) noexcept(false) {    
    lua_getglobal(_script, "sum");
    lua_pushnumber(_script, x);
    lua_pushnumber(_script, y);
    if (lua_pcall(_script, 2, 1, 0) != LUA_OK) {
        std::string luaError = lua_tostring(_script, -1);
        std::cout << "Failed to run script!\n" << luaError << '\n';
        return -1;
    }
    answer = static_cast<int>(lua_tonumber(_script, -1));
    lua_pop(_script, 1);

    return 0;
}

/* Closeing Scripter */
Scripter::~Scripter() noexcept {
    lua_close(_script);
}
