#pragma once

#include <string>
#include <iostream>

#include "excepts.hpp"

#ifdef _WIN32
    #define _OUTPUT_TYPE ".exe"
    #define _EXECUTER_SYMBOL ".\\"
    #define _INCLUDE_PATH "C:\\Ccraft\\include"
#else
    #define _OUTPUT_TYPE ".out"
    #define _EXECUTER_SYMBOL "./"
    #define _INCLUDE_PATH "/usr/ccraft/include"
#endif

std::string replaceSubstring(const std::string& original, const std::string& toReplace, const std::string& replacement) {
    std::string result = original;
    size_t pos = 0;

    while ((pos = result.find(toReplace, pos)) != std::string::npos) {
        result.replace(pos, toReplace.length(), replacement);
        pos += replacement.length();
    }

    return result;
}

int _do_build(std::string lang_type, std::string file_path)
{
    std::string file_path1 = replaceSubstring(file_path, ".", "");
        file_path1 = replaceSubstring(file_path1, "\\", "");

    if (lang_type == "c") {
        // compilation
        std::string _command = 
            "clang -w -ffast-math " + file_path + " -o _spec_" + file_path1 + _OUTPUT_TYPE + " -O3 " +
            "-I" + _INCLUDE_PATH;
        
        // executing
        std::string _e_e = "_spec_", _e_command = 
            _EXECUTER_SYMBOL + _e_e + file_path1 + _OUTPUT_TYPE;
    }
    else /* c++ */ {
        // compilation
        std::string _command = 
            "clang++ -w -ffast-math " + file_path + " -o _spec_" + file_path1 + _OUTPUT_TYPE + " -O3 " +
            "-I" + _INCLUDE_PATH;
        
        // executing
        std::string _e_e = "_spec_", _e_command = 
            _EXECUTER_SYMBOL + _e_e + file_path1 + _OUTPUT_TYPE;
        
        // dev log
        // std::cout << "command: " << _command << "\n_e_command: " << _e_command << "\n";
        system(_command.c_str());
        system(_e_command.c_str());
    }

    return 0;
}

int do_build(std::string lang_type, std::string file_path)
{
    try
    {
        int _x = _do_build(lang_type, file_path);

        if (_x != 0)
        {
            throw CompilationException("compilation terminated with code <" + std::to_string(_x) + ">");
        }
    }
    catch (CompilationException &e)
    {
        std::cerr << "ccraft: compilation error: " << e.what() << '\n';
        exit(-1);
    }
    catch (const std::exception &e)
    {
        std::cerr << "ccraft: error: " << e.what() << '\n';
    }

    return 0;
}