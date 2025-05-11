local action = _ACTION or ""

workspace "nanovg"
    location "build"
    configurations { "Debug", "Release" }
    platforms { "native", "x64", "x32" }

project "nanovg"
    kind "StaticLib"
    language "C"
    includedirs { "src" }
    files { "src/*.c" }
    targetdir "build"
    defines { "_CRT_SECURE_NO_WARNINGS" }

    filter "configurations:Debug"
        defines { "DEBUG" }
        symbols "On"
        warnings "Extra"

    filter "configurations:Release"
        defines { "NDEBUG" }
        optimize "On"
        warnings "Extra"

function setup_example(name, file, extra_defines)
    project(name)
        kind "ConsoleApp"
        language "C"
        files { file, "example/demo.c", "example/perf.c" }
        includedirs { "src", "example" }
        targetdir "build"
        links { "nanovg" }
        if extra_defines then
            defines(extra_defines)
        end

        filter "system:linux"
            linkoptions { "`pkg-config --libs glfw3`" }
            links { "GL", "GLU", "m", "GLEW" }
            defines { "NANOVG_GLEW" }

        filter "system:windows"
            links { "glfw3", "gdi32", "winmm", "user32", "GLEW", "glu32", "opengl32", "kernel32" }
            defines { "NANOVG_GLEW", "_CRT_SECURE_NO_WARNINGS" }

        filter "system:macosx"
            links { "glfw3" }
            linkoptions { "-framework OpenGL", "-framework Cocoa", "-framework IOKit", "-framework CoreVideo", "-framework Carbon" }

        filter "configurations:Debug"
            defines { "DEBUG" }
            symbols "On"
            warnings "Extra"

        filter "configurations:Release"
            defines { "NDEBUG" }
            optimize "On"
            warnings "Extra"
end

setup_example("example_gl2",     "example/example_gl2.c")
setup_example("example_gl3",     "example/example_gl3.c")
setup_example("example_gl2_msaa","example/example_gl2.c", { "DEMO_MSAA" })
setup_example("example_gl3_msaa","example/example_gl3.c", { "DEMO_MSAA" })
setup_example("example_fbo",     "example/example_fbo.c")
setup_example("example_gles2",   "example/example_gles2.c")
setup_example("example_gles3",   "example/example_gles3.c")
