function basicWorkspace (name)
    workspace(name)
    architecture "x86_64"
    configurations {
        "Debug",
        "Release"
    }
    filter "configurations:Debug" 
        symbols "On"
    filter "configurations:Release"
        optimize "Speed"
    filter {}
    
    includedirs {
        "."
    }
    
    filter "system:macosx" 
        cppdialect "C++20"
        staticruntime "On"
    filter {}
    
    filter "system:windows"
    
        buildoptions { "/Zc:__cplusplus", "/Zc:preprocessor", "/MP" }
    
    filter {}
    
    targetdir("Build/Bin/%{cfg.longname}")
    objdir("Build/Obj/%{cfg.longname}")
    
    cppdialect "C++20"
    
    end