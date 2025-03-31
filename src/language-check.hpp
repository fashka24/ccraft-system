#pragma once

#include <string>
#include <map>

#include "excepts.hpp"

#define DO_PAIR(left, right) {left, right},

std::map<std::string, std::string> langs = {
    // c++
    DO_PAIR("cpp", "c++")
    DO_PAIR("c++", "c++")
    DO_PAIR("cxx", "c++")
    DO_PAIR("cc", "c++")
    // c
    DO_PAIR("c", "c")
    DO_PAIR("cpp", "c")

};

std::string _get_file_ext(const std::string file, std::string _default = "unk") {
    size_t dotPosition = file.find_last_of('.');

    if (dotPosition != std::string::npos && dotPosition != 0) {
        return file.substr(dotPosition + 1);
    }
    return _default;
}


std::string do_language_check(std::string path) {
    std::string _ext = _get_file_ext(path);

    if (_ext == "unk") {
        throw FileExtensionException("The file extension of file <" +path+ "> cannot be processed");
        return "unk";
    }

    return langs.at(_ext);
}

#undef DO_PAIR