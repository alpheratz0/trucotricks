# SPDX-License-Identifier: GPL-2.0-only © 2025 <alpheratz99@protonmail.com>

PREFIX ?= /usr/local

PKG_CONFIG ?= pkg-config

VERSION = v$(shell cat VERSION)

# linux/windows
TARGET ?= linux

# on/off
DEBUG ?= off

ifeq ($(TARGET),linux)
	CC ?= gcc
	DEPENDENCIES = glfw3 gl sdl2 SDL2_mixer
	INCS = $(shell $(PKG_CONFIG) --cflags $(DEPENDENCIES)) -Iinclude -I/usr/include/nanovg
	LIBS = $(shell $(PKG_CONFIG) --libs $(DEPENDENCIES)) -lnanovg -lm
	OUTNAME = trucotricks
else ifeq ($(TARGET),windows)
	CC = x86_64-w64-mingw32-gcc
	INCS = \
		-I./third_party/include/nanovg/ \
		-I./third_party/include/glfw3/ \
		-I./third_party/include/sdl2/ \
		-I./third_party/include/sdl2_mixer/ \
		-I./third_party/include/gles3/ \
		-Iinclude
	LIBS = \
		-L./third_party/lib/glfw3/ \
		-L./third_party/lib/sdl2/ \
		-L./third_party/lib/sdl2_mixer/ \
		-L./third_party/lib/nanovg/ \
		-L./third_party/lib/gles3/ \
		-lopengl32 -lmingw32 -lglfw3 -lSDL2main -lSDL2 -lSDL2_mixer -lgdi32 -lnanovg -mwindows
	OUTNAME = trucotricks.exe
endif

ifeq ($(DEBUG),on)
	DEBUG_FLAGS = -DDebug
endif

TRUCOTRICKS_CFLAGS = -std=c11 -Wall -O2 $(INCS) \
				  -DVersion=$(VERSION) $(DEBUG_FLAGS) \
				  $(CPPFLAGS) $(CFLAGS)

TRUCOTRICKS_LDFLAGS = -s $(LIBS) $(LDFLAGS)
