// stdlib
#include <iostream>

// lib
#include "src/version.h"
#include "src/language-check.hpp"
#include "src/builder.hpp"

// main
int main(int argc, char const *argv[])
{
    if (argc == 1) {
        std::cout << "ccraft [" _CCRAFT_VERSION "] build system\n";
        return 0;
    }
    else if (argc == 2) {
        std::string _path = argv[1];
        
        try
        {
            std::string _lang = do_language_check(_path);

            int _Cx = do_build(_lang, _path);
        }
        catch(const std::exception& e)
        {
            std::cerr << "ccraft: error: " << e.what() << '\n';
            return -1;
        }
        
    }

    return 0;
}
