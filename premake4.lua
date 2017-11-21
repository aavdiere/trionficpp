#!lua

-- Set clang as compiler
premake.gcc.cc = 'clang'
premake.gcc.cxx = 'clang++'

-- A solution contains projects, and defines the available configurations
solution "trionfi"
configurations { "debug", "release" }
platforms { "x32", "x64" }

-- A project defines one build target
project "trionfi"
    kind "ConsoleApp"
    language "C++"
    buildoptions { "-std=c++1z" }
    files { "src/*.cpp" }
    includedirs { "include", "dependencies/dynet/dynet" }
    libdirs { "dependencies/dynet/build/dynet/" }
    objdir "bin/intermediate"
    prebuildcommands { "cd dependencies/dynet/ && mkdir -p build && cd build && cmake .. -DEIGEN3_INCLUDE_DIR=../../eigen && make -j 4 && cd ../../../" }
    
    configuration "debug"
        defines { "DEBUG" }
        buildoptions {
            "-fsanitize=address"
        }
        linkoptions {
            "-fsanitize=address"
        }
        flags { "Symbols" }
        targetdir "bin/debug"

    configuration "release"
        targetdir "bin/release"
        defines { "NDEBUG" }
        flags { "Optimize" }
