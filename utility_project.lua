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
<<<<<<< HEAD
    "utl/**.cc",
    "mtl/**.hpp",
    "mtl/**.cpp",
    "mtl/**.cc",
=======
    "utl/**.h",
    "utl/**.cc",
    "mtl/**.hpp",
    "mtl/**.cpp"
>>>>>>> 7fb59ccaef9831cf8b2aed71e2e18cee100a22e5
}