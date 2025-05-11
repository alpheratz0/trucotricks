// SPDX-License-Identifier: GPL-2.0-only © 2025 <alpheratz99@protonmail.com>

#include <stdio.h>
#include <string.h>
#include <SDL_mixer.h>
#include <SDL_thread.h>
#include <nanovg.h>
#include <stdbool.h>
#include <stdlib.h>
#include <trucotricks/debug.h>
#include <trucotricks/fs.h>
#include <trucotricks/resource_loader.h>

Tt_Resource_Loader *Tt_Resource_Loader_New(size_t nResources, Tt_Resource_Info *resources, NVGcontext *vg)
{
	Tt_Resource_Loader *rl = malloc(sizeof(Tt_Resource_Loader));

	if (!vg)
		Fatal(("No NanoVG context supplied"));

	rl->isLoading = false;
	rl->progress = 0.0f;
	rl->nResources = nResources;
	rl->loaderThread = NULL;
	rl->resourcesFullSize = 0;
	rl->vg = vg;

	memset(rl->message, 0, sizeof(rl->message));
	memcpy(rl->resources, resources,
			nResources * sizeof(Tt_Resource_Info));

	for (size_t i = 0; i < nResources; ++i) {
		rl->resources[i].size = Tt_FS_Get_Size(rl->resources[i].path);
		if (rl->resources[i].size < 0)
			Fatal(("Couldn't get file size for: %s", rl->resources[i].path));
		rl->resourcesFullSize += rl->resources[i].size;
	}

	return rl;
}

static int __Tt_Resource_Loader_Start_Thread_Function(void *userdata)
{
	Tt_Resource_Loader *rl = userdata;
	long processedSize = 0;

	for (size_t i=0; i < rl->nResources; ++i) {
		Tt_Resource_Info *resource = &rl->resources[i];

		snprintf(rl->message, sizeof(rl->message), "Loading %s %s...",
				Tt_Resource_Kind_To_String(resource->kind), resource->path);

		D((rl->message));

		processedSize += resource->size;
		rl->progress = ((float)(processedSize) / (rl->resourcesFullSize)) * 100;

		switch (resource->kind) {
		case RESOURCE_KIND_FONT:
			if ((*resource->font.handle = nvgCreateFont(rl->vg, resource->path, resource->path)) < 0)
				Fatal(("Failed to load font: %s", resource->path));
			break;
		case RESOURCE_KIND_TEXTURE:
			// Defer texture loading (to gpu) to Tt_Resource_Loader_Generate_Textures
			resource->texture.data = Tt_FS_Get_Content(resource->path);
			break;
		case RESOURCE_KIND_SOUND:
			if ((*resource->sound.handle = Mix_LoadWAV(resource->path)) == NULL)
				Fatal(("Failed to load sound: %s", resource->path));
			break;
		}
	}

	rl->isLoading = false;

	return 0;
}

void Tt_Resource_Loader_Start(Tt_Resource_Loader *rl)
{
	if (rl->loaderThread || rl->isLoading)
		return;

	memset(rl->message, 0, sizeof(rl->message));
	rl->isLoading = true;
	rl->progress = 0.0f;
	rl->loaderThread = SDL_CreateThread(
			__Tt_Resource_Loader_Start_Thread_Function, "Resource Loader", rl);
}

void Tt_Resource_Loader_Generate_Textures(Tt_Resource_Loader *rl)
{
	for (size_t i=0; i < rl->nResources; ++i) {
		Tt_Resource_Info *resource = &rl->resources[i];
		if (resource->kind != RESOURCE_KIND_TEXTURE) continue;
		D(("Uploading texture %s to gpu...", resource->path));
		if ((*resource->texture.handle = nvgCreateImageMem(rl->vg, RESOURCE_TEXTURE_FLAGS,
						(unsigned char *)resource->texture.data, resource->size)) == 0)
			Fatal(("Failed to load texture to gpu: %s", resource->path));
		free(resource->texture.data);
	}
}

void Tt_Resource_Loader_Free(Tt_Resource_Loader *rl)
{
	if (rl->loaderThread)
		SDL_WaitThread(rl->loaderThread, NULL);
	free(rl);
}
