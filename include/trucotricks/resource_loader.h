// SPDX-License-Identifier: GPL-2.0-only © 2025 <alpheratz99@protonmail.com>

#ifndef TRUCOTRICKS_RESOURCE_LOADER_H
#define TRUCOTRICKS_RESOURCE_LOADER_H

#include <SDL_mixer.h>
#include <SDL_thread.h>
#include <nanovg.h>
#include <stdbool.h>

#define RESOURCE_TEXTURE_FLAGS \
	(NVG_IMAGE_REPEATX | \
	 NVG_IMAGE_REPEATY | \
	 NVG_IMAGE_NEAREST)

#define RESOURCE_LOADER_MAX_TEXTURES (100)

#define Tt_Resource_Generic(k,t,p,h) {.kind = k, .path = p, .t  = {.handle = h }}
#define Tt_Resource_Font(p,h) Tt_Resource_Generic(RESOURCE_KIND_FONT, font, p, h)
#define Tt_Resource_Texture(p,h) Tt_Resource_Generic(RESOURCE_KIND_TEXTURE, texture, p, h)
#define Tt_Resource_Sound(p,h) Tt_Resource_Generic(RESOURCE_KIND_SOUND, sound, p, h)

#define Tt_Resource_Kind_To_String(rk) \
	(rk == RESOURCE_KIND_FONT ? "font" : \
		rk == RESOURCE_KIND_TEXTURE ? "texture" : \
			rk == RESOURCE_KIND_SOUND ? "sound" : \
				"unknown")

typedef struct Tt_Resource_Info Tt_Resource_Info;
typedef struct Tt_Resource_Loader Tt_Resource_Loader;

enum Tt_Resource_Kind {
	RESOURCE_KIND_FONT,
	// Make sure to call `resourcesGenTextures`
	// from a valid GL context after the texture
	// data is loaded.
	RESOURCE_KIND_TEXTURE,
	RESOURCE_KIND_SOUND
};

struct Tt_Resource_Info {
	enum Tt_Resource_Kind kind;
	const char *path;
	long size;
	union {
		struct { int *handle; } font;
		struct { int *handle; char *data; } texture;
		struct { Mix_Chunk **handle; } sound;
	};
};

struct Tt_Resource_Loader {
	// Resources count
	size_t nResources;
	// Resources
	Tt_Resource_Info resources[RESOURCE_LOADER_MAX_TEXTURES];
	// Thread where the resources are being loaded
	SDL_Thread *loaderThread;
	// Current message, something like `Loading X stuff...`
	char message[512];
	// Progress (1-100)
	double progress;
	// True if the resources are being loaded
	bool isLoading;
	// Total size of all the resources combined
	long resourcesFullSize;
	// Nanovg context
	NVGcontext *vg;
};

Tt_Resource_Loader *Tt_Resource_Loader_New(size_t nResources, Tt_Resource_Info *resources, NVGcontext *vg);

void Tt_Resource_Loader_Start(Tt_Resource_Loader *rl);

void Tt_Resource_Loader_Generate_Textures(Tt_Resource_Loader *rl);

void Tt_Resource_Loader_Free(Tt_Resource_Loader *rl);

#endif
