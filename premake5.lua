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

<<<<<<< HEAD
filter "system:macosx" 
    cppdialect "C++20"
    staticruntime "On"
filter {}
=======
>>>>>>> 7fb59ccaef9831cf8b2aed71e2e18cee100a22e5



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
<<<<<<< HEAD
    "."
=======
    ".", "UtilityTest"
>>>>>>> 7fb59ccaef9831cf8b2aed71e2e18cee100a22e5
}

files { 
    "UtilityTest/**.hpp",
    "UtilityTest/**.cpp"
}

links "Utility"

-----------------------------------------------------------------------------------------
-- Project Playground
-----------------------------------------------------------------------------------------
<<<<<<< HEAD
=======

>>>>>>> 7fb59ccaef9831cf8b2aed71e2e18cee100a22e5
project "Playground"
location "."
kind "ConsoleApp"
language "C++"
<<<<<<< HEAD

sysincludedirs {
    "."
}


=======
>>>>>>> 7fb59ccaef9831cf8b2aed71e2e18cee100a22e5
filter { "system:macosx"} 
    xcodebuildsettings { 

    }
filter {}

files { 
    "Playground/**.hpp",
    "Playground/**.cpp"
}
links "Utility"