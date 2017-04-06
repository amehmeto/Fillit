/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit_square_vs_tetri.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amehmeto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/06 20:43:11 by amehmeto          #+#    #+#             */
/*   Updated: 2017/04/06 20:43:16 by amehmeto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

#define TETRI_SQUARE1  ((t[i][0] & s[0]) || (t[i][1] & s[1]))
#define TETRI_SQUARE2	((t[i][2] & s[2]) || (t[i][3] & s[3]))

/*
** **************************************************************************
*/

static void		shift_by_one(unsigned long long t[27][4], int i)
{
	t[i][3] >>= 1;
	t[i][3] |= ((t[i][2] & 1) << 63);
	t[i][2] >>= 1;
	t[i][2] |= ((t[i][1] & 1) << 63);
	t[i][1] >>= 1;
	t[i][1] |= ((t[i][0] & 1) << 63);
	t[i][0] >>= 1;
}

static void		remove_t_from_square(unsigned long long t[27][4],
										unsigned long long square[4], int i)
{
	square[0] -= t[i][0];
	square[1] -= t[i][1];
	square[2] -= t[i][2];
	square[3] -= t[i][3];
}

static void		put_t_in_square(unsigned long long t[27][4],
									unsigned long long square[4], int i)
{
	square[0] ^= t[i][0];
	square[1] ^= t[i][1];
	square[2] ^= t[i][2];
	square[3] ^= t[i][3];
}

static void		one_t_cpy(unsigned long long t_src[4],
								unsigned long long t_dst[4])
{
	t_dst[0] = t_src[0];
	t_dst[1] = t_src[1];
	t_dst[2] = t_src[2];
	t_dst[3] = t_src[3];
}

int				square_vs_t(unsigned long long s[4],
							unsigned long long t[27][4], int i)
{
	unsigned long long		t_cpy[4];
	int						ret;

	if (t[i][0] == ~(0ULL))
		return (i + 27);
	while (TETRI_SQUARE1 || TETRI_SQUARE2)
		shift_by_one(t, i);
	if (!t[i][0] && !t[i][1] && !t[i][2] && !t[i][3])
		return (i);
	put_t_in_square(t, s, i);
	one_t_cpy(t[i + 1], t_cpy);
	while (t[i + 1][0] != ~(0ULL) && (ret = square_vs_t(s, t, i + 1)) < 27)
	{
		one_t_cpy(t_cpy, t[i + 1]);
		remove_t_from_square(t, s, i);
		shift_by_one(t, i);
		while (TETRI_SQUARE1 || TETRI_SQUARE2)
			shift_by_one(t, i);
		if (!t[i][0] && !t[i][1] && !t[i][2] && !t[i][3])
			return (i);
		put_t_in_square(t, s, i);
	}
	put_t_in_square(t, s, i);
	return (square_vs_t(s, t, i + 1));
}
