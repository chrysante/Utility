project "catch"
location "."
kind "StaticLib"
language "C++"

includedirs {
    "include/catch"
}

files { 
    "catch_amalgamated.cpp"
}

filter "system:linux"
    buildoptions "-fPIC"
filter {}
