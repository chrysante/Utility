include "premake-common.lua"

newoption {
    trigger = "tests",
    description = "Generate Unit Test Projects"
}

-----------------------------------------------------------------------------------------
-- Workspace utility
-----------------------------------------------------------------------------------------
basic_workspace "utility"

-----------------------------------------------------------------------------------------
-- Project mtl-test
-----------------------------------------------------------------------------------------
project "mtl-test"
test_project_setup()
files { 
    "test/mtl/**.hpp",
    "test/mtl/**.cpp"
}
defines { "MTL_AVX=1", "UTL_ASSERT_WITH_EXCEPTIONS=1" }
filter { "system:macosx" }
    buildoptions { "-mavx" }
filter {}

-----------------------------------------------------------------------------------------
-- Project utl-test-all
-----------------------------------------------------------------------------------------
project "utl-test-all"
test_project_setup()
files { 
    "test/utl/**.hpp",
    "test/utl/**.cpp"
}
links { "utility" }

-----------------------------------------------------------------------------------------
-- Project utl-test-ilist
-----------------------------------------------------------------------------------------
project "utl-test-ilist"
test_project_setup()
files { 
    "test/utl/LifetimeCounter.hpp",
    "test/utl/LifetimeCounter.cpp",
    "test/utl/ilist.t.cpp"
}
links { "utility" }

-----------------------------------------------------------------------------------------
-- Project utl-test-dyncast
-----------------------------------------------------------------------------------------
project "utl-test-dyncast"
test_project_setup()
files { 
    "test/utl/dyncast.t.cpp"
}
--links { "utility" }

-----------------------------------------------------------------------------------------
-- Project utl-test-variant
-----------------------------------------------------------------------------------------
project "utl-test-variant"
test_project_setup()
files { 
    "test/utl/variant.t.cpp"
}

-----------------------------------------------------------------------------------------
-- Project utl-test-function
-----------------------------------------------------------------------------------------
project "utl-test-function"
test_project_setup()
files { 
    "test/utl/function.t.cpp",
    "test/utl/function_view.t.cpp"
}

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
