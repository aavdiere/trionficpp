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
    includedirs { "include" }
    objdir "bin/intermediate"
    
    configuration "debug"
        defines { "DEBUG" }
        buildoptions {
--            "-fsanitize=address"
        }
        linkoptions {
--            "-fsanitize=address"
        }
        flags { "Symbols" }
        targetdir "bin/debug"

    configuration "release"
        targetdir "bin/release"
        defines { "NDEBUG" }
        buildoptions { "-03" }
        flags { "Optimize" }
