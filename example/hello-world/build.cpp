#include <CcraftAPI.hpp>

int main()
{
    ccraft(USE_CPP_20, "main.cpp",
        "hello-world" BASIC_OUTPUT_TYPE,
        "-O3"
    );

    return 0;
}