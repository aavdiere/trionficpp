#!lua

-- A solution contains projects, and defines the available configurations
solution "trionfi"
configurations { "debug", "release" }
platforms { "x32", "x64" }

-- A project defines one build target
project "trionfi"
    kind "ConsoleApp"
    language "C++"
    buildoptions {"-std=c++1z"}
    files { "src/*.cpp" }
    includedirs { "include" }
    objdir "bin/intermediate"
    
    configuration "debug"
        defines { "DEBUG" }
        flags { "Symbols" }
        targetdir "bin/debug"

    configuration "release"
        targetdir "bin/release"
        defines { "NDEBUG" }
        flags { "Optimize" }