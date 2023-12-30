function basic_workspace (name)
    workspace(name)
    architecture "x86_64"

    configurations {
        "Debug",
        "Development",
        "Release"
    }

    filter "configurations:Debug" 
        symbols "On"
    filter "configurations:Development or Release"
        filter "system:linux"
            buildoptions "-O1" -- probably due to a compiler bug the ilist move assignment test fails on higher optimization levels
            defines "NDEBUG"

        filter "system:not linux"
            optimize "Speed"
            defines "NDEBUG"
    filter {}

    filter { "configurations:Debug" }
        defines { "UTL_DEBUG_LEVEL=2", "MTL_DEBUG_LEVEL=1" } -- MTL_DEBUG_LEVEL=1 is on purpose
    filter { "configurations:Development" }
        defines { "UTL_DEBUG_LEVEL=1", "MTL_DEBUG_LEVEL=1" }
    filter { "configurations:Release"  }
        defines { "UTL_DEBUG_LEVEL=0", "MTL_DEBUG_LEVEL=0" }
    filter {}
    
    
    cppdialect "C++20"
    staticruntime "On"
   
    filter "system:windows" 
        buildoptions { "/Zc:__cplusplus", "/Zc:preprocessor", "/MP" }
        systemversion ("latest")
    filter "system:macosx"
        
    filter {}
    

    targetdir("build/bin/%{cfg.longname}")
    objdir("build/obj/%{cfg.longname}")
end

function test_project_setup()
    location "."
    kind "ConsoleApp"
    language "C++"    

    includedirs "test"

    externalincludedirs {
        "include", "external/catch/include"
    }

    links { "catch" }
end
