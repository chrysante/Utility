-----------------------------------------------------------------------------------------
-- Workspace Utility
-----------------------------------------------------------------------------------------
workspace "Utility"
architecture "x86_64"
configurations {
    "Debug",
    "Release"
}
filter "configurations:Debug" 
    symbols "On"
filter "configurations:Release"
    optimize "Speed"
filter {}

includedirs {
    "."
}

filter "system:macosx" 
    cppdialect "C++20"
    staticruntime "On"
filter {}
newoption {
    trigger = "tests",
    description = "Generate Unit Test Projects"
 }

targetdir("Build/Bin/%{cfg.longname}")
objdir("Build/Obj/%{cfg.longname}")

-----------------------------------------------------------------------------------------
-- Project Utility
-----------------------------------------------------------------------------------------
include "utility_project.lua"

-----------------------------------------------------------------------------------------
-- Project UtilityTest
-----------------------------------------------------------------------------------------
project "UtilityTest"
location "."
kind "ConsoleApp"
language "C++"    

externalincludedirs {
    "."
}

files { 
    "UtilityTest/**.hpp",
    "UtilityTest/**.cpp"
}

links "Utility"

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

files { 
    "Playground/**.hpp",
    "Playground/**.cpp"
}
links "Utility"