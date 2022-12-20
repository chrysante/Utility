project "utility"

location "."
kind "StaticLib"
language "C++"
externalincludedirs "include"

files { 
    "include/utl/**.h",
    "include/utl/**.hpp",
    "src/**.cpp",
    "src/**.cc",
}