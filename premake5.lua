include "premake-common.lua"

newoption {
    trigger = "tests",
    description = "Generate Unit Test Projects"
}

-----------------------------------------------------------------------------------------
-- Workspace utility
-----------------------------------------------------------------------------------------
basicWorkspace("utility")

-----------------------------------------------------------------------------------------
-- Project mtl-test
-----------------------------------------------------------------------------------------
project "mtl-test"
location "."
kind "ConsoleApp"
language "C++"    

includedirs "test"

externalincludedirs {
    "include", "external/catch2/include"
}

files { 
    "test/mtl/**.hpp",
    "test/mtl/**.cpp"
}

defines { "MTL_AVX=1", "UTL_ASSERT_WITH_EXCEPTIONS=1" }

filter { "system:macosx" }
    buildoptions { "-mavx" }
filter {}

links { "catch" }

-----------------------------------------------------------------------------------------
-- Project utl-test-all
-----------------------------------------------------------------------------------------
project "utl-test-all"
location "."
kind "ConsoleApp"
language "C++"    

includedirs "test"

externalincludedirs {
    "include", "external/catch/include"
}

files { 
    "test/utl/**.hpp",
    "test/utl/**.cpp"
}

links { "utility", "catch" }

-----------------------------------------------------------------------------------------
-- Project utl-test-ilist
-----------------------------------------------------------------------------------------
project "utl-test-ilist"
location "."
kind "ConsoleApp"
language "C++"    

includedirs "test"

externalincludedirs {
    "include", "external/catch/include"
}

files { 
    "test/utl/LifetimeCounter.hpp",
    "test/utl/LifetimeCounter.cpp",
    "test/utl/ilist.t.cpp"
}

links { "utility", "catch" }

-----------------------------------------------------------------------------------------
-- Project code-gen
-----------------------------------------------------------------------------------------
project "code-gen"
location "."
kind "ConsoleApp"
language "C++"
filter { "system:macosx"} 
    defines { "PROJECT_LOCATION=\"../../..\"" } -- use different (maybe less fragile) solution for windows
filter {}

files { 
    "code-gen/**.hpp",
    "code-gen/**.cpp"
}

defines { "PROJECT_LOCATION=\"../../..\"" }

-----------------------------------------------------------------------------------------
-- Project benchmark
-----------------------------------------------------------------------------------------
project "benchmark"
location "."
kind "ConsoleApp"
language "C++"
filter { "system:macosx"} 
    xcodebuildsettings { 

    }
filter {}

externalincludedirs {
    "include", "external/benchmark/include"
}

files { 
    "benchmark/**.hpp",
    "benchmark/**.cpp"
}

links { "utility", "benchmark_lib" }

-----------------------------------------------------------------------------------------
-- Project playground
-----------------------------------------------------------------------------------------
project "playground"
location "."
kind "ConsoleApp"
language "C++"
filter { "system:macosx"} 
    xcodebuildsettings { 

    }
filter {}

externalincludedirs {
    "include"
}

files { 
    "playground/**.hpp",
    "playground/**.cpp"
}

links "utility"

-----------------------------------------------------------------------------------------
-- Other projects
-----------------------------------------------------------------------------------------

include "lib.lua"
include "external/benchmark"
include "external/catch"
