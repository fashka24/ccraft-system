# Useful Functions

## Macros: `BASIC_OUTPUT_TYPE`

This macro defines the type of extension used for running files based on the operating system.

| Operating System | File Extension |
|------------------|----------------|
| Windows          | `.exe`         |
| Linux            | (**none**)     |
| MacOS            | (**none**)     |

## Function: `replace`

This is implementation of function `replace` for C.

```cpp
char* replace(const char* str, const char* old_substr, const char* new_substr);
```

## Macros: **C/C++ version**

| Macro            | Version |
|------------------|---------|
| `USE_NOTHING`    | (none)  |
| `USE_C`          | C lang  |
| `USE_CPP_11`     | C++11   |
| `USE_CPP_14`     | C++14   |
| `USE_CPP_17`     | C++17   |
| `USE_CPP_20`     | C++20   |
| `USE_CPP_23`     | C++23   |
| `USE_CPP_26`     | C++26   |