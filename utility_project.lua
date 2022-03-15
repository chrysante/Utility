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