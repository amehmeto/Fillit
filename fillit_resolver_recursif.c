/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit_resolver_recursif.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amehmeto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/06 04:17:01 by amehmeto          #+#    #+#             */
/*   Updated: 2017/04/06 05:40:41 by amehmeto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

/*
** **************************************************************************
*/

static void		shift_by_one(unsigned long long tetri[27][4], int i)
{
	tetri[i][3] >>= 1;
	tetri[i][3] |= ((tetri[i][2] & 1) << 63);
	tetri[i][2] >>= 1;
	tetri[i][2] |= ((tetri[i][1] & 1) << 63);
	tetri[i][1] >>= 1;
	tetri[i][1] |= ((tetri[i][0] & 1) << 63);
	tetri[i][0] >>= 1;
}

static void		remove_tetri_from_square(unsigned long long tetri[27][4],
										unsigned long long square[4], int i)
{
	square[0] -= tetri[i][0];
	square[1] -= tetri[i][1];
	square[2] -= tetri[i][2];
	square[3] -= tetri[i][3];
}

static void		put_tetri_in_square(unsigned long long tetri[27][4],
									unsigned long long square[4], int i)
{
	square[0] ^= tetri[i][0];
	square[1] ^= tetri[i][1];
	square[2] ^= tetri[i][2];
	square[3] ^= tetri[i][3];
}

static int		square_vs_tetri(unsigned long long square[4],
								unsigned long long tetri[27][4], int i)
{
	unsigned long long		tetri_cpy[4];
	int						ret;

	if (tetri[i][0] == ~(0ULL))
		return (i + 27);
	while ((tetri[i][0] & square[0]) || (tetri[i][1] & square[1]) ||
			(tetri[i][2] & square[2]) || (tetri[i][3] & square[3]))
		shift_by_one(tetri, i);
	if (!tetri[i][0] && !tetri[i][1] && !tetri[i][2] && !tetri[i][3])
		return (i);
	put_tetri_in_square(tetri, square, i);
//	fillit(&tetri_cpy, &tetri[i + 1]);
	tetri_cpy[0] = tetri[i + 1][0];
	tetri_cpy[1] = tetri[i + 1][1];
	tetri_cpy[2] = tetri[i + 1][2];
	tetri_cpy[3] = tetri[i + 1][3];
//	fillit(&tetri[i + 1], &tetri_cpy);
	while (tetri[i + 1][0] != ~(0ULL) &&
			(ret = square_vs_tetri(square, tetri, i + 1)) < 27)
	{
		tetri[i + 1][0] = tetri_cpy[0];
		tetri[i + 1][1] = tetri_cpy[1];
		tetri[i + 1][2] = tetri_cpy[2];
		tetri[i + 1][3] = tetri_cpy[3];
		remove_tetri_from_square(tetri, square, i);
		shift_by_one(tetri, i);
		while ((tetri[i][0] & square[0]) || (tetri[i][1] & square[1]) ||
				(tetri[i][2] & square[2]) || (tetri[i][3] & square[3]))
			shift_by_one(tetri, i);
		if (!tetri[i][0] && !tetri[i][1] && !tetri[i][2] && !tetri[i][3])
			return (i);
		put_tetri_in_square(tetri, square, i);
	}
	put_tetri_in_square(tetri, square, i);
	return (square_vs_tetri(square, tetri, i + 1));
}

int				fillit_resolver(unsigned long long tetri[27][4])
{
	unsigned long long		temp_tetri[27][4];
	unsigned long long		square[4];
	int						size;
	int						i;
	int						j;

	square[0] = 0;
	square[1] = 0;
	square[2] = 0;
	square[3] = 0;
	size = 2;
	i = -1;
	while (size)
	{
		j = 0;
		grid_init(square, size);
		tetri_cpy(tetri, temp_tetri);
		i = square_vs_tetri(square, temp_tetri, j);
		size++;
		if (i > 27)
			break ;
	}
	fillit_displayer(temp_tetri, size - 1, (i > 27) ? i - 27 : i);
	return (1);
}
