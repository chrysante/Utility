include "premakeCommon.lua"

newoption {
    trigger = "tests",
    description = "Generate Unit Test Projects"
}

-----------------------------------------------------------------------------------------
-- Workspace Utility
-----------------------------------------------------------------------------------------
basicWorkspace("Utility")

includedirs {
    "."
}

-----------------------------------------------------------------------------------------
-- Project Utility
-----------------------------------------------------------------------------------------
include "premake5.lua"

-----------------------------------------------------------------------------------------
-- Project UtilityTest
-----------------------------------------------------------------------------------------
project "UtilityTest"
location "."
kind "ConsoleApp"
language "C++"    

sysincludedirs {
    ".", "UtilityTest"
}

files { 
    "UtilityTest/**.hpp",
    "UtilityTest/**.cpp"
}

defines { "MTL_AVX=1" }

filter { "system:macosx" }
    buildoptions { "-mavx" }

links "Utility"

-----------------------------------------------------------------------------------------
-- Project CodeGenerators
-----------------------------------------------------------------------------------------
project "CodeGenerators"
location "."
kind "ConsoleApp"
language "C++"
filter { "system:macosx"} 
    defines { "PROJECT_LOCATION=\"../../..\"" } -- use different (maybe less fragile) solution for windows
    xcodebuildsettings { 

    }
filter {}

files { 
    "CodeGenerators/**.hpp",
    "CodeGenerators/**.cpp"
}

defines { "PROJECT_LOCATION=\"../../..\"" }

-----------------------------------------------------------------------------------------
-- Project Benchmark
-----------------------------------------------------------------------------------------
project "Benchmark"
location "."
kind "ConsoleApp"
language "C++"
filter { "system:macosx"} 
    xcodebuildsettings { 

    }
filter {}

sysincludedirs {
    ".", "benchmark_lib/include"
}

files { 
    "Benchmark/**.hpp",
    "Benchmark/**.cpp"
}
links { "Utility", "benchmark_lib" }

-----------------------------------------------------------------------------------------
-- Project Playground
-----------------------------------------------------------------------------------------
project "Playground"
location "."
kind "ConsoleApp"
language "C++"
filter { "system:macosx"} 
    xcodebuildsettings { 

    }
filter {}

sysincludedirs {
    "."
}

files { 
    "Playground/**.hpp",
    "Playground/**.cpp"
}
links "Utility"

-----------------------------------------------------------------------------------------
-- Project benchmark_lib
-----------------------------------------------------------------------------------------
project "benchmark_lib"
location "."
kind "StaticLib"
language "C++"
filter { "system:macosx"} 
    xcodebuildsettings { 

    }
filter {}

sysincludedirs {
    "benchmark_lib/include",
}

files { 
    "benchmark_lib/src/**.h",
    "benchmark_lib/src/**.cc"
}
