function basicWorkspace (name)
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
        optimize "Speed"
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
    filter {}
    
    targetdir("Build/Bin/%{cfg.longname}")
    objdir("Build/Obj/%{cfg.longname}")
    
    end