-- premake5.lua
--require "dlls"

workspace "Maze"
    location ""
    configurations { "Debug", "Release" }
    platforms { "Win32", "Win64" }

    filter { "platforms:Win32" }
        system "Windows"
        architecture "x86"

    filter { "platforms:Win64" }
        system "Windows"
        architecture "x64"
    filter { }

project "maze_generation"
    kind "ConsoleApp"
    language "C++"
    location "solution"
    targetdir "solution/bin/%{cfg.buildcfg}/%{cfg.architecture}/"

    files {
        "./source/main.cpp",
        "./source/**.h", "./source/**.cpp"
    }
    removefiles{
        "./source/unit_tests/**"
    }

    includedirs {
    }


    --Debug and Release configurations
    filter "configurations:Debug"
        defines { "DEBUG" }
        symbols "On"

    filter "configurations:Release"
        defines { "NDEBUG" }
        optimize "On"

    filter { }

project "unit_tests"
    kind "ConsoleApp"
    language "C++"
    location "solution"
    targetdir "solution/bin/%{cfg.buildcfg}/%{cfg.architecture}/"

    files { "./source/unit_tests/*.cpp", "./source/unit_tests/*.h"}

    includedirs {
    }


    --Debug and Release configurations
    filter "configurations:Debug"
        defines { "DEBUG" }
        symbols "On"

    filter "configurations:Release"
        defines { "NDEBUG" }
        optimize "On"

    filter { }