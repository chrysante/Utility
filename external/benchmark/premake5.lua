project "benchmark-lib"
location "."
kind "StaticLib"
language "C++"

externalincludedirs {
    "include",
}

files { 
    "src/**.h",
    "src/**.cc"
}
