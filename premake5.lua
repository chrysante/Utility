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

targetdir("Build/Bin/%{cfg.longname}")
objdir("Build/Obj/%{cfg.longname}")

-----------------------------------------------------------------------------------------
-- Project Utility
-----------------------------------------------------------------------------------------
project "Utility"
location "."
kind "StaticLib"
language "C++"
filter "system:macosx" 
    xcodebuildsettings { 

    }
filter {}
    

files { 
    "utl/**.hpp",
    "utl/**.cpp",
    "utl/**.cc",
    "mtl/**.hpp",
    "mtl/**.cpp",
    "mtl/**.cc",
}

-----------------------------------------------------------------------------------------
-- Project UtilityTest
-----------------------------------------------------------------------------------------
project "UtilityTest"
location "."
kind "ConsoleApp"
language "C++"    

sysincludedirs {
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

sysincludedirs {
    "."
}


filter { "system:macosx"} 
    xcodebuildsettings { 

    }
filter {}

files { 
    "Playground/**.hpp",
    "Playground/**.cpp"
}
links "Utility"