#include "scripter.h"
#include <iomanip>

int main() {

    Sorokin::Scripter script;

    /* getUser from SQL test
    const char* filename = "/home/student/lua/sqltest.lua";
    */
    /* getMaps table test
    */
    const char* filename = "/home/student/lua/tabletest.lua";

    if (script.setScriptFile(filename)) {
        return -1;
    }
    script.openLibs();
    if (script.runScript() != LUA_OK) {
        return -1;
    }

    std::unordered_multimap<std::string, std::string> numbers;
    if (script.getMaps(numbers)) {
        return -1;
    }

    for (const auto& iter : numbers) {
        std::cout << iter.first << ": " << iter.second << '\n';
    }

    /* getUser from SQL test
    Sorokin::user Dranga;
    if (script.getUser("Dranga", Dranga)) {
        return -1;
    }


    std::cout << Dranga._id
              << " | " << Dranga._fname << std::setw(11)
              << "| " << Dranga._lname << std::setw(11)
              << "| " << Dranga._job << std::setw(11) << '\n';
    */

    return 0;
}







