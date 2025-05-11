// SPDX-License-Identifier: GPL-2.0-only © 2025 <alpheratz99@protonmail.com>

#ifndef TRUCOTRICKS_ANIMATED_DEBUG_H
#define TRUCOTRICKS_ANIMATED_DEBUG_H

#include <stdio.h>
#include <stdlib.h>

// Colors used
#define Cyan "\033[1;33;40m"
#define Yellow "\033[1;36;40m"
#define Green "\033[1;32;40m"
#define Red "\033[1;31;40m"

// Helper macro, prints filename, line number and message in the
// specified color.
#define _Dbg(c,a) do { \
	printf(c "%s:%u: ", __FILE__, __LINE__); \
	printf a; putchar('\n'); fflush(stdout); \
	printf("\033[0;10m"); \
} while (0)

#define Fatal(a) do{_Dbg(Red,a);exit(1);}while(0)

#if defined(Debug)
#define I(a) _Dbg(Cyan,a)
#define D(a) _Dbg(Yellow,a)
#define V(a) _Dbg(Green,a)
#else
#define I(a)
#define D(a)
#define V(a)
#endif

#endif
