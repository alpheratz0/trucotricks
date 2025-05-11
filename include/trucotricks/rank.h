// SPDX-License-Identifier: GPL-2.0-only © 2025 <alpheratz99@protonmail.com>

#ifndef TRUCOTRICKS_RANK_H
#define TRUCOTRICKS_RANK_H

#define Tt_Rank_To_String(rank) \
	rank == RANK_UNO ? "1" : \
		rank == RANK_DOS ? "2" : \
			rank == RANK_TRES ? "3" : \
				rank == RANK_CUATRO ? "4" : \
					rank == RANK_CINCO ? "5" : \
						rank == RANK_SEIS ? "6" : \
							rank == RANK_SIETE ? "7" : \
								rank == RANK_DIEZ ? "10" : \
									rank == RANK_ONCE ? "11" : \
										"12"

enum Tt_Rank
{
	RANK_UNO,
	RANK_DOS,
	RANK_TRES,
	RANK_CUATRO,
	RANK_CINCO,
	RANK_SEIS,
	RANK_SIETE,
	RANK_DIEZ,
	RANK_ONCE,
	RANK_DOCE,
	RANK_COUNT,
	RANK_INVALID
};

#endif
