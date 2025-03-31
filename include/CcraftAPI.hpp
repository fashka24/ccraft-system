#pragma once

/* API created for C/C++
*/

// For C use:
/* extern "C++"
*/

// DevLog

bool DEVLOG_IS_ON = true;

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

    DO_CHRCHR(ls_flags) = "";
    DO_CHRCHR(ls_includes) = "";
    DO_CHRCHR(ls_include_paths) = "";
};

char* _get_existing_compiler() {
    bool _gcc = access(_GCC_UCRT_PATH "gcc" _BASIC_OUTPUT_TYPE, 0);
    bool _clang = access(_CLANG_BASIC_PATH "clang" _BASIC_OUTPUT_TYPE, 0);

    if (_gcc && _clang) return "clang";

    if (_gcc) return "gcc";
    else if (_clang) return "clang";
    
    return "unk";
}


char* replace(const char* str, const char* old_substr, const char* new_substr) {
    if (!str || !old_substr || !new_substr) {
        return NULL;
    }

    if (strlen(old_substr) == 0) {
        return strdup(str);
    }

    int count = 0;
    const char* temp = str;
    while ((temp = strstr(temp, old_substr)) != NULL) {
        count++;
        temp += strlen(old_substr);
    }

    size_t new_length = strlen(str) + count * (strlen(new_substr) - strlen(old_substr));
    char* result = (char*)malloc(new_length + 1);
    if (!result) {
        return NULL;
    }

    char* pos = result;
    while (*str) {
        if (strstr(str, old_substr) == str) {
            strcpy(pos, new_substr);
            pos += strlen(new_substr);
            str += strlen(old_substr);
        } else {
            *pos++ = *str++;
        }
    }
    *pos = '\0';

    return result;
}

char* do_concat(BuildScript *_script) {
    // printf("[devlog] start evaluating length\n");

    size_t totalLength = strlen(_script->as_compiler) + strlen(_script->as_target) +
                         strlen(_script->as_output) + strlen(_script->as_optimization) +
                         strlen(_script->as_optimization) + strlen(_script->ls_includes) + 
                         strlen(_script->ls_includes) + strlen(_script->ls_include_paths) +
                         strlen(_script->as_output_flag) + 7; // +7

    // printf("[devlog] total length: %d\n", (int) totalLength);
    // printf("[devlog] real len: %d\n", totalLength * sizeof(char*));
                         
    char* result = (char*)malloc(totalLength * sizeof(char*));
    if (result == NULL) {
        return NULL;
    }

    // printf("[devlog] sizeof: %d\n", (int) sizeof(result));
    // printf("[devlog] strlen: %d\n", (int) strlen(result));

    snprintf(result, totalLength, "%s %s %s %s %s %s %s %s",
    _script->as_compiler, _script->ls_flags, _script->as_target,
    _script->ls_includes, _script->as_output_flag, _script->as_output,
    _script->as_optimization, _script->ls_include_paths);

    return result; // 
}

int do_build(BuildScript *script) {
    printf("[info] concating BuildScript...\n");

    DO_CHR(_command) = do_concat(script);

    if (_command == NULL) {
        perror("[error] unable to merge BuildScript\n");
        exit(-1);
    }

    printf("[success] concated BuildScript!\n");

    DO_CHR(__command) = replace(_command, "  ", " ");

    printf("[info] compilation: %s\n", __command);

    return system(_command);
    // return 0;
}

int _CCRAFT(int c_cpp_version, 
    char* _target = "main.cpp", 
    char* _output = "a" _BASIC_OUTPUT_TYPE,
    char* _flags = "",
    char* _optimization = "")
{
    char* _existing_compiler = _get_existing_compiler();

    // Check if a valid compiler was found
    if (strcmp(_existing_compiler, "unk") != 0) {
        perror("[error] not found any compilers (gcc or clang)\n");
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
            printf("[info] using C, compiler <%s>\n", _existing_compiler);
            _script.as_output_flag = "-o";
            break;
        case USE_CPP_11:
            printf("[info] using C++11, compiler <%s>\n", _existing_compiler);
            _script.as_output_flag = "-std=c++11 -o";
            break;
        case USE_CPP_14:
            printf("[info] using C++14, compiler <%s>\n", _existing_compiler);
            _script.as_output_flag = "-std=c++14 -o";
            break;
        case USE_CPP_17:
            printf("[info] using C++17, compiler <%s>\n", _existing_compiler);
            _script.as_output_flag = "-std=c++17 -o";
            break;
        case USE_CPP_20:
            printf("[info] using C++20, compiler <%s>\n", _existing_compiler);
            _script.as_output_flag = "-std=c++20 -o";
            break;
        case USE_CPP_23:
            printf("[info] using C++23, compiler <%s>\n", _existing_compiler);
            _script.as_output_flag = "-std=c++23 -o";
            break;
        case USE_CPP_26:
            printf("[info] using C++26, compiler <%s>\n", _existing_compiler);
            _script.as_output_flag = "-std=c++26 -o";
            break;
        default:
            perror("[error] unknown or unsupported C/C++ technical standard");
            exit(-1);
    }

    // Call the build function with the populated script
    printf("[info] start building\n");

    int xoutput = do_build(&_script);

    if (xoutput != 0) {
        perror("[error] compilation finished with the errors\n");
        exit(-1);
    }

    printf("[success] compilation finished without the errors\n");

    return 0;
}

#define ccraft _CCRAFT
#define BASIC_OUTPUT_TYPE _BASIC_OUTPUT_TYPE