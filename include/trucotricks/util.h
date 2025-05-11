// SPDX-License-Identifier: GPL-2.0-only © 2025 <alpheratz99@protonmail.com>

#ifndef TRUCOTRICKS_UTIL_H
#define TRUCOTRICKS_UTIL_H

#define Tt_Length(arr) (sizeof(arr) / sizeof(arr[0]))
#define Tt_Swap(type,a,b) do { type ____a = a; a = b; b = ____a; } while (0)
#define Tt_Min(a,b) ((a) < (b) ? (a) : (b))
#define Tt_Max(a,b) ((a) > (b) ? (a) : (b))
#define Tt_Clamp(a, min, max) ((a) < (min) ? (min) : ((a) > (max) ? (max) : (a)))
#define Tt_Sign(d) ((d > 0) - (d < 0))
#define Tt_Loop(v, l) ((((v) % (l)) + l) % l)
#define nvgText2(ctx,x,y,str,end) nvgText(ctx,(int)(x), (int)(y), str, end)

#endif
