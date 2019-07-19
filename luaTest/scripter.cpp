#include "scripter.h"


using namespace Sorokin;

/* Methods setting the Scripter obj up */
Scripter::Scripter() noexcept(false) {
    _script = luaL_newstate();
    if (_script == NULL) {
        throw std::bad_alloc();
    }
}
int Scripter::setScriptFile(const char *scriptFileName) noexcept {
    lua_settop(_script, 0);
    if (luaL_loadfile(_script, scriptFileName) != LUA_OK) {
        std::cout << "Failed to load file!\n";
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
int Scripter::getUser(const char *lname, user &answer) noexcept(false) {
    const char* functionName = "getUser";

    // Clear stack
    lua_settop(_script, 0);

    // Run function
    if (lua_getglobal(_script, functionName) != LUA_TFUNCTION) {
        std::cout << "Failed to find function!\n";
        return -1;
    }
    if (lua_pushstring(_script, lname) == NULL) {
        std::cout << "Failed to push string!\n";
        return -1;
    }
    if (lua_pcall(_script, 1, 1, 0) != LUA_OK) {
        const char* luaError = lua_tostring(_script, -1);
        std::cout << "Failed to run script!\n" << luaError << '\n';
        return -1;
    }
    lua_pushnil(_script);
    while (lua_next(_script, -2) != 0) {
        const char* key = lua_tostring(_script, -2);
        if (!strcmp(key, "id")) {
            answer._id = lua_tostring(_script, -1);
        }
        else if (!strcmp(key, "fname")) {
            answer._fname = lua_tostring(_script, -1);
        }
        else if (!strcmp(key, "lname")) {
            answer._lname = lua_tostring(_script, -1);
        }
        else if (!strcmp(key, "job")) {
            answer._job = lua_tostring(_script, -1);
        }
        else {
            std::cout << "Unknown key! Reading was stopped!\n";
            return -1;
        }
        lua_pop(_script, 1);
    }

    // Clear stack
    lua_settop(_script, 0);

    return 0;
}
int Scripter::getMaps(std::unordered_multimap<std::string, std::string>& answer) noexcept(false) {
    const char* functionName = "createTables";

    lua_settop(_script, 0);
    if (lua_getglobal(_script, functionName) != LUA_TFUNCTION) {
        std::cout << "Failed to find function!\n";
        return -1;
    }
    if (lua_pcall(_script, 0, 1, 0) != LUA_OK) {
        const char* luaError = lua_tostring(_script, -1);
        std::cout << "Failed to run script!\n" << luaError << '\n';
        return -1;
    }
    if (this->findValueFromTable(answer) != 0) {
        return -1;
    }

    return 0;
}

int Scripter::findValueFromTable(std::unordered_multimap<std::string, std::string> &answer) noexcept(false) {
    if (!lua_checkstack(_script, 2)) {
        std::cout << "Not enough stack space!\n";
        return -1;
    }

    lua_pushnil(_script);
    while (lua_next(_script, -2) != 0) {
        switch (lua_type(_script, -1)) {
        case LUA_TNUMBER:
            answer.insert(std::pair<std::string, std::string>(this->getStringKey(), this->getStringValue()));
            break;
        case LUA_TBOOLEAN:
            answer.insert(std::pair<std::string, std::string>(this->getStringKey(), this->getStringValue()));
            break;
        case LUA_TSTRING:
            answer.insert(std::pair<std::string, std::string>(this->getStringKey(), this->getStringValue()));
            break;
        case LUA_TTABLE:
            if (this->findValueFromTable(answer)) {
                return -1;
            }
            break;
        default:
            std::cout << "Unknown userdata! Process interrupted!\n";
            return -1;
        }
        lua_pop(_script, 1);
    }

    return 0;
}

std::string Scripter::getStringKey() noexcept {
    switch (lua_type(_script, -2)) {
    case LUA_TNUMBER:
        return std::to_string(static_cast<int>(lua_tonumber(_script, -2)));
    case LUA_TSTRING:
        return lua_tostring(_script, -2);
    case LUA_TBOOLEAN:
        return lua_toboolean(_script, -2) ? "true" : "false";
    default:
        return "Unable to read key";
    }
}
std::string Scripter::getStringValue() noexcept {
    switch (lua_type(_script, -1)) {
    case LUA_TNUMBER:
        return std::to_string(lua_tonumber(_script, -1));
    case LUA_TSTRING:
        return lua_tostring(_script, -1);
    case LUA_TBOOLEAN:
        return lua_toboolean(_script, -1) ? "true" : "false";
    default:
        return "Unable to read value";
    }
}

/* Closeing Scripter */
Scripter::~Scripter() noexcept {
    lua_close(_script);
}
