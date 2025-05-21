project "App"
   kind "ConsoleApp"
   language "C++"
   cppdialect "C++20"
   targetdir "Binaries/%{cfg.buildcfg}"
   staticruntime "off"

   files { "Source/**.h", "Source/**.cpp", "Source/**.hpp" }

   includedirs
   {
      "Source",

	  -- Include Core
	  "../Core/Source",
      "../Vendor/Binaries/SFML-3.0.0/include"
   }

   libdirs
    {
        "../Vendor/Binaries/SFML-3.0.0/lib",
        "../Vendor/Binaries/SFML-3.0.0/lib/Debug"
    }   

   links
   {
      "Core"
   }

   defines
    {
        "SFML_STATIC"
    }

   targetdir ("../Binaries/" .. OutputDir .. "/%{prj.name}")
   objdir ("../Binaries/Intermediates/" .. OutputDir .. "/%{prj.name}")

   filter "system:windows"
       systemversion "latest"
       defines { "WINDOWS" }

   filter "configurations:Debug"
       defines { "DEBUG" }
       runtime "Debug"
       symbols "On"
       links 
       {
            "sfml-graphics-s-d.lib",
            "sfml-window-s-d.lib",
            "sfml-audio-s-d.lib",
            "sfml-network-s-d.lib",
            "sfml-system-s-d.lib",

            "opengl32.lib",
            "freetyped.lib",
            "winmm.lib",
            "gdi32.lib",
            "FLACd.lib",
            "vorbisencd.lib",
            "vorbisfiled.lib",
            "vorbisd.lib",
            "oggd.lib",
            "ws2_32.lib"
       }

   filter "configurations:Release"
       defines { "RELEASE" }
       runtime "Release"
       optimize "On"
       symbols "On"
       links 
       {
            "sfml-graphics-s.lib",
            "sfml-window-s.lib",
            "sfml-audio-s.lib",
            "sfml-network-s.lib",
            "sfml-system-s.lib",

            "opengl32.lib",
            "freetype.lib",
            "winmm.lib",
            "gdi32.lib",
            "FLAC.lib",
            "vorbisenc.lib",
            "vorbisfile.lib",
            "vorbis.lib",
            "ogg.lib",
            "ws2_32.lib"
       }

   filter "configurations:Dist"
       defines { "DIST" }
       runtime "Release"
       optimize "On"
       symbols "Off"
       links 
       {
            "sfml-graphics-s.lib",
            "sfml-window-s.lib",
            "sfml-audio-s.lib",
            "sfml-network-s.lib",
            "sfml-system-s.lib",

            "opengl32.lib",
            "freetype.lib",
            "winmm.lib",
            "gdi32.lib",
            "FLAC.lib",
            "vorbisenc.lib",
            "vorbisfile.lib",
            "vorbis.lib",
            "ogg.lib",
            "ws2_32.lib"
       }