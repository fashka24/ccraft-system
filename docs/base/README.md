# Base documentation

This is base documentation of ccraft build system.

## Get started

1. Create a new folder and create into it two files: `main.cpp`, `build.cpp`
2. Write to `build.cpp` basic code:
```cpp
#include <CcraftAPI.hpp>   // ccraft api for dev build scripts.

int main() {
    ccraft(
        USE_CPP_17,        // The 17th C++ standard will be used.
        "main.cpp"         // Main file
    );
}
```
3. Start building and execute output file

```bash
ccraft build.cpp
./a.exe
```

## Syntax `ccraft`

```cpp
int _CCRAFT(
    int c_cpp_version, 
    char* _target = "main.cpp", 
    char* _output = "a" _BASIC_OUTPUT_TYPE, // _BASIC_OUTPUT_TYPE: ".exe" (win), "" (linux)
    char* _flags = "",
    char* _optimization = ""
);
```