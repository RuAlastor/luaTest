#include "scripter.h"

int main() {

    Sorokin::Scripter script;

    const char* filename1 = "/home/student/lua/sqltest.lua";

    if (script.setScriptFile(filename1)) {
        return -1;
    }
    script.openLibs();
    if (script.runScript() != LUA_OK) {
        return -1;
    }

    /*
    lua_State* _script = luaL_newstate();
    if (_script == NULL) {
        std::cout << "Failed to allocate memory!\n";
        return -1;
    }
    int result = luaL_loadfile(_script, filename1);
    if (result != LUA_OK) {
        std::cout << "Failed to load file!\n";
        return -1;
    }
    luaL_openlibs(_script);
    result = lua_pcall(_script, 0, 0, 0);
    if (result != LUA_OK) {
        std::string luaError = lua_tostring(_script, -1);
        std::cout << "Failed to run script!\n" << luaError << '\n';
        return -1;
    }
    */

    return 0;
}







