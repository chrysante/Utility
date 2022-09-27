project "Utility"
location "."
kind "StaticLib"
language "C++"
filter "system:macosx" 
    xcodebuildsettings { 

    }
filter {}
    
defines "UTL_ASSERT_WITH_EXCEPTIONS=1"

files { 
    "utl/**.hpp",
    "utl/**.cpp",
    "utl/**.h",
    "utl/**.cc",
    "mtl/**.hpp",
    "mtl/**.cpp"
}