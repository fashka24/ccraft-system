#pragma once

/* API created for C/C++
*/

// For C use:
/* extern "C++"
*/

// C/C++ versions

#define USE_NOTHING -1
#define USE_C 1
#define USE_CPP_11 2
#define USE_CPP_14 3
#define USE_CPP_17 4
#define USE_CPP_20 5
#define USE_CPP_23 6
#define USE_CPP_26 7

// main code

#ifdef _WIN32
    #define _OUTPUT_TYPE ".exe"
    #define _BASIC_OUTPUT_TYPE ".exe"
    #define _GCC_UCRT_PATH "C:\\msys64\\ucrt64\\bin\\"
    #define _CLANG_BASIC_PATH "C:\\Program Files\\LLVM\\bin\\"
#else
    #define _OUTPUT_TYPE ".out"
    #define _BASIC_OUTPUT_TYPE ""
    #define _GCC_UCRT_PATH "/usr/bin/"
    #define _CLANG_BASIC_PATH "/usr/bin/"
#endif

#define DO_CHR(name) char* name
#define DO_CHRCHR(name) char* name

#include <stdio.h>
#include <io.h>
#include <stdlib.h>
#include <string.h>

struct BuildScript
{
    // as - one word object
    // ls - many words object

    DO_CHR(as_compiler) = "clang";
    DO_CHR(as_target)   = "main.c";
    DO_CHR(as_output)   = "a." _OUTPUT_TYPE;
    DO_CHRCHR(as_output_flag) = "-o";
    DO_CHR(as_optimization) = "-O3";

    DO_CHRCHR(ls_flags);
    DO_CHRCHR(ls_includes);
    DO_CHRCHR(ls_include_paths);
};

char* _get_existing_compiler() {
    bool _gcc = access(_GCC_UCRT_PATH "gcc" _BASIC_OUTPUT_TYPE, 0);
    bool _clang = access(_CLANG_BASIC_PATH "clang" _BASIC_OUTPUT_TYPE, 0);

    if (_gcc && _clang) return "clang";

    if (_gcc) return "gcc";
    else if (_clang) return "clang";
    
    return "unk";
}

char* do_concat(BuildScript *_script) {
    size_t totalLength = strlen(_script->as_compiler) + strlen(_script->as_target) +
                         strlen(_script->as_output)+ strlen(_script->as_optimization) +
                         strlen(_script->as_optimization) + strlen(_script->ls_includes) + 
                         strlen(_script->ls_includes) + strlen(_script->ls_include_paths) +
                         strlen(_script->as_output_flag) + 4; // +4
                         
    char* result = (char*)malloc(totalLength * sizeof(char));
    if (result == NULL) {
        return NULL;
    }

    strcpy(result, _script->as_compiler);
    strcat(result, " ");
    strcat(result, _script->as_target);
    if (strlen(_script->ls_includes) != 0) {
        strcat(result, " ");
        strcat(result, _script->ls_includes);
    }
    strcat(result, " ");
    strcat(result, _script->as_output_flag);
    strcat(result, " ");
    strcat(result, _script->as_output);
    strcat(result, " ");
    strcat(result, _script->as_optimization);
    if (strlen(_script->ls_flags) != 0) {
        strcat(result, " ");
        strcat(result, _script->ls_flags);
    }
    if (strlen(_script->ls_include_paths) != 0) {
        strcat(result, " ");
        strcat(result, _script->ls_include_paths);
    }

    return result;
}

int do_build(BuildScript *script) {
    DO_CHR(_command) = do_concat(script);

    printf("[info] compilation: %s", _command);
    // return system(_command);
    return 0;
}

int _CCRAFT(int c_cpp_version, 
    char* _target = "main.cpp", 
    char* _output = "a" _OUTPUT_TYPE,
    char* _flags = "",
    char* _optimization = "")
{
    char* _existing_compiler = _get_existing_compiler();

    // Check if a valid compiler was found
    if (strcmp(_existing_compiler, "unk") == 0) {
        perror("[error] not found any compilers (gcc or clang)");
        exit(-1);
    }

    // Determine the compiler to use based on the C/C++ version
    if (c_cpp_version != USE_C && c_cpp_version != USE_NOTHING) {
        _existing_compiler = strdup((strcmp( _existing_compiler, "gcc") == 0) ? "clang++" : "g++");
    }

    // Handle the case where no version is specified
    if (c_cpp_version == USE_NOTHING) {
        printf("[exit] nothing used version, exit...\n");
        exit(0);
    }

    // Initialize BuildScript structure
    BuildScript _script;
    _script.as_compiler = _existing_compiler;
    _script.as_optimization = _optimization;
    _script.as_target = _target;
    _script.as_output = _output;
    _script.ls_flags = _flags;

    // Set the output flag and standard based on the C/C++ version
    switch (c_cpp_version) {
        case USE_C:
            printf("[info] using C, compiler %s\n", _existing_compiler);
            _script.as_output_flag = "-o";
            break;
        case USE_CPP_11:
            printf("[info] using C++11, compiler %s\n", _existing_compiler);
            _script.as_output_flag = "-std=c++11 -o";
            break;
        case USE_CPP_14:
            printf("[info] using C++14, compiler %s\n", _existing_compiler);
            _script.as_output_flag = "-std=c++14 -o";
            break;
        case USE_CPP_17:
            printf("[info] using C++17, compiler %s\n", _existing_compiler);
            _script.as_output_flag = "-std=c++17 -o";
            break;
        case USE_CPP_20:
            printf("[info] using C++20, compiler %s\n", _existing_compiler);
            _script.as_output_flag = "-std=c++20 -o";
            break;
        case USE_CPP_23:
            printf("[info] using C++23, compiler %s\n", _existing_compiler);
            _script.as_output_flag = "-std=c++23 -o";
            break;
        case USE_CPP_26:
            printf("[info] using C++26, compiler %s\n", _existing_compiler);
            _script.as_output_flag = "-std=c++26 -o";
            break;
        default:
            perror("[error] unknown or unsupported C/C++ technical standard");
            exit(-1);
    }

    // Call the build function with the populated script
    do_build(&_script);

    return 0;
}

#define ccraft _CCRAFT