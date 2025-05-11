// SPDX-License-Identifier: GPL-2.0-only © 2025 <alpheratz99@protonmail.com>

#include <SDL_error.h>
#define GLFW_INCLUDE_ES3
#define GLFW_INCLUDE_GLEXT
#include <GLFW/glfw3.h>
#include <SDL.h>
#include <SDL_mixer.h>
#define NANOVG_GLES3_IMPLEMENTATION
#include <nanovg.h>
#include <nanovg_gl.h>
#include <stdio.h>
#include <trucotricks/app_icon.h>
#include <trucotricks/debug.h>
#include <trucotricks/window.h>

#define FORCE_WINDOWED

GLFWwindow *gWindow = NULL;
NVGcontext *gVg = NULL;
double gWindowWidth = WINDOW_INITIAL_WIDTH;
double gWindowHeight = WINDOW_INITIAL_HEIGHT;

void Tt_Window_Create(void)
{
	D(("Initializing SDL audio..."));
	if (SDL_Init(SDL_INIT_AUDIO) < 0)
		Fatal(("Couldn't initialize SDL audio: %s.", SDL_GetError()));

	D(("Initializing SDL mixer..."));
	if (Mix_Init(MIX_INIT_OGG) != MIX_INIT_OGG)
		Fatal(("Couldn't initialize SDL mixer: %s.", Mix_GetError()));
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024) < 0)
		Fatal(("Couldn't initialize SDL mixer: %s.", Mix_GetError()));

	D(("Initializing GLFW..."));
	if (glfwInit() == GLFW_FALSE)
		Fatal(("Couldn't initialize GLFW: ec=%d.", glfwGetError(NULL)));

	D(("Setting up GLFW window hints..."));
#if defined(FORCE_WINDOWED)
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
#else
	glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
#endif
	glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

	D(("Creating GLFW window..."));
	gWindow = glfwCreateWindow(WINDOW_INITIAL_WIDTH, WINDOW_INITIAL_HEIGHT,
			WINDOW_TITLE, NULL, NULL);

	Tt_Icon *appIcon = Tt_Get_App_Icon();

	GLFWimage icon = {0};
	icon.width = appIcon->width;
	icon.height = appIcon->height;
	icon.pixels = appIcon->pixels;
	glfwSetWindowIcon(gWindow, 1, &icon);

	D(("Setting up GLFW window..."));
	glfwMakeContextCurrent(gWindow);
	glfwSetWindowSizeLimits(gWindow, 640, 510, GLFW_DONT_CARE, GLFW_DONT_CARE);
	glfwSwapInterval(0);
	glfwSetTime(0);

#if defined(FORCE_WINDOWED)
	glfwSetWindowAttrib(gWindow, GLFW_RESIZABLE, GLFW_TRUE);
#endif

	D(("Creating NVG GLES3 context..."));
	if (!(gVg = nvgCreateGLES3(NVG_ANTIALIAS|NVG_STENCIL_STROKES)))
		Fatal(("Couldn't create NVG GLES3 context."));
}

void Tt_Window_Destroy(void)
{
	D(("Deinitializing SDL audio..."));
	Mix_CloseAudio();
	Mix_Quit();
	D(("Deinitializing SDL..."));
	SDL_Quit();
	D(("Deleting NVG GLES3 context..."));
	nvgDeleteGLES3(gVg);
	D(("Terminating GLFW..."));
	glfwTerminate();
}
