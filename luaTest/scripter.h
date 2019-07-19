/**
 * @file scripter.h
*/
#ifndef SCRIPTER_H
#define SCRIPTER_H

#include <iostream>
#include <cstring>
#include <string>
#include <exception>
#include <unordered_map>

extern "C" {
    #include <lua.h>
    #include <lauxlib.h>
    #include <lualib.h>
}


namespace Sorokin {

    /// @brief Data struct returned from SQL-db
    struct user {
        std::string _id;
        std::string _fname;
        std::string _lname;
        std::string _job;
    };

    /// @brief Class calls scripts from *.lua files
    /// @example main.cpp
    class Scripter {

    public:
        /**
          * @defgroup General-methods
          * @brief Methods required to create script object and correctly load scripts from file
          */
        /// @{
        /**
         * @brief Scripter - default constructor
         * @throw std::bad_alloc if was unable to allocate memory for script-object
         */
        Scripter() noexcept(false);
        /**
         * @brief setScriptFile loads lua-script.
         * @param[in] scriptFileName - script-file location
         * @return 0 if no error occured, -1 else
         *
         * Clears stack, then loads lua-script from the file.
         */
        int setScriptFile(const char* scriptFileName) noexcept;
        /// @brief openLibs opens standart lua-libaries for loaded scripts
        inline void openLibs() noexcept {
            luaL_openlibs(_script);
        }
        /**
         * @brief runScript - runs loaded script
         * @return 0 if no error occured, -1 else
         */
        int runScript() noexcept;
        ~Scripter() noexcept;
        /// @}



        /**
         * @defgroup Specific-methods
         * @brief Methods required to call specific functions from already loaded scripts
         */
        /// @{
        /**
         * @brief getUser gets user info from SQL-db
         * @param[in] lname - key to search user in db
         * @param[out] answer - struct to load info into
         * @return 0 if no error occured, -1 else
         *
         * Calls <getUser> function from loaded lua-script with <lname> as key to search.
         * Recieves lua-table back on the stack.
         * Gets info.
         */
        int getUser(const char* lname, user& answer) noexcept(false);
        /**
         * @brief getMaps reads tables created by lua-script
         * @param[out] answer - container to put key-value pairs from lua-tables
         * @return 0 if no error occured, -1 else
         *
         * Calls <<createTables> function from loaded lua-script.
         * Calls <this->getValuesFromTable> method to get pairs from table
         */
        int getMaps(std::unordered_multimap<std::string, std::string>& answer) noexcept(false);
        /// @}

    private:
        /// @brief _script - lua structure to address the stack
        lua_State* _script;

        /// @defgroup deleted methods
        /// @{
        /// @brief Scripter - deleted copy constructor
        Scripter(const Scripter&) = delete;
        /// @brief Scripter - deleted move constructor
        Scripter(Scripter&&) = delete;
        /// @brief Deleted copy assignement operator
        Scripter& operator =(const Scripter&) = delete;
        /// @brief Deleted move assignement operator
        Scripter& operator =(Scripter&&) = delete;
        /// @}

        /**
         * @brief findValueFromTable parses table on the top of the stack
         * @param[out] answer - container to put key-value pairs from lua-tables
         * @return 0 if no error occured, -1 else
         *
         * Recursevly parses table on the top of the stack
         * Puts recieved pairs into the <answer> map
         */
        int findValueFromTable(std::unordered_multimap<std::string, std::string>& answer) noexcept(false);
        /**
         * @brief getStringKey gets string from beneath the top element on the stack
         * @return std::string, if error occured returns "Unable to read key"
         */
        std::string getStringKey() noexcept;
        /**
         * @brief getStringValue gets string from the top element on the stack
         * @return std::string, if error occured returns "Unable to read value"
         */
        std::string getStringValue() noexcept;
    };

}


#endif // SCRIPTER_H
