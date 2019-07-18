#ifndef SCRIPTER_H
#define SCRIPTER_H

#include <iostream>
#include <cstring>
#include <string>
#include <unordered_map>

extern "C" {
    #include <lua.h>
    #include <lauxlib.h>
    #include <lualib.h>
}


namespace Sorokin {

    struct user {
        std::string _id;
        std::string _fname;
        std::string _lname;
        std::string _job;
    };

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
        int getUser(const char* lname, user& answer) noexcept(false);
        int getMaps(std::unordered_multimap<std::string, std::string>& answer) noexcept(false);

        /* Close Scripter */
        ~Scripter() noexcept;

    private:
        lua_State* _script;

        Scripter(const Scripter& other) = delete;
        Scripter(Scripter&& other) = delete;
        Scripter& operator =(const Scripter& other) = delete;
        Scripter& operator =(Scripter&& other) = delete;

        int findValueFromTable(std::unordered_multimap<std::string, std::string>& answer) noexcept(false);
        std::string getKey() noexcept;
        std::string getStringValue() noexcept;
    };

}


#endif // SCRIPTER_H
