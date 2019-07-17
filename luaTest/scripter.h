#ifndef SCRIPTER_H
#define SCRIPTER_H

#include <iostream>

extern "C" {
    #include <lua.h>
    #include <lauxlib.h>
    #include <lualib.h>
}


namespace Sorokin {

    class Scripter {

    public:
        /* Methods to set up Scripter */
        Scripter() noexcept(false);
        int setScriptFile(const char* scriptFileName) noexcept;
        inline void openLibs() noexcept {
            luaL_openlibs(_script);
        }
        int runScript() noexcept;

        /* Run specific function from script file */
        int modifyCharArray(const std::string& toModify, std::string& modified) noexcept(false);
        int sumTwo(int& x, int& y, int& answer) noexcept(false);

        /* Close Scripter */
        ~Scripter() noexcept;

    private:
        lua_State* _script;

        Scripter(const Scripter& other) = delete;
        Scripter(Scripter&& other) = delete;
        Scripter& operator =(const Scripter& other) = delete;
        Scripter& operator =(Scripter&& other) = delete;

    };

}


#endif // SCRIPTER_H
