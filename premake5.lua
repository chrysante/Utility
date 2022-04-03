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




--workspace "Utility"
--architecture "x86_64"
--configurations {
--    "Debug",
--    "Release"
--}
--filter "configurations:Debug" 
--    symbols "On"
--filter "configurations:Release"
--    optimize "Speed"
--filter {}

--includedirs {
--    "."
--}

--filter "system:macosx" 
--    cppdialect "C++20"
--    staticruntime "On"
--filter {}
--newoption {
--    trigger = "tests",
--    description = "Generate Unit Test Projects"
-- }

--filter "system:windows"

--    buildoptions { "/Zc:__cplusplus", "/Zc:preprocessor", "/MP" }

--filter {}

--targetdir("Build/Bin/%{cfg.longname}")
--objdir("Build/Obj/%{cfg.longname}")

--cppdialect "C++20"

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