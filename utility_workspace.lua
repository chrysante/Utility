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