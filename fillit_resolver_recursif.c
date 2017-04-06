/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit_resolver.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amehmeto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/25 21:26:50 by amehmeto          #+#    #+#             */
/*   Updated: 2017/04/06 02:15:16 by amehmeto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

/*
 ** **************************************************************************
 */

void			grid_init(unsigned long long square[4], int size)
{
	unsigned long long	*quartr_to_fill;
	unsigned long long	marker;
	int					size_cpy;
	int					i;
	int					j;

	quartr_to_fill = NULL;
	size_cpy = size;
	i = -1;
	j = 0;
	while (++i < size)
	{
//		printf("\033[33mi = %d\nj = %d \t j * 4 = %d \t (j + 1) * 4 = %d \n\033[0m"
//												,	i, j, j * 4, (j + 1) * 4);
		if (i >= j * 4 && i < (j + 1) * 4)
		{
			quartr_to_fill = &square[j++];
			*quartr_to_fill = 0;
		}
		//		printf("j = %d\n", j);
		marker = 0x8000000000000000;
		*quartr_to_fill >>= 16;
		size_cpy = size;
		while (size_cpy--)
		{
			*quartr_to_fill ^= marker;
			marker >>= 1;
		}
	}
	j = -1;
	while (++j < 4 && square[j] != ~(0ULL))
		square[j] = ~square[j];
	//	j = -1;
	//	while (++j < 4)
	//		printf("square[%d] = %llu\n", j, square[j]);
}

/*
** **************************************************************************
*/

void			tetri_cpy(unsigned long long tetri[27][4],
		unsigned long long temp_tetri[27][4])
{
	int		i;
	int		j;

	i = -1;
	while (++i < 27)
	{
		j = -1;
		while (++j < 4)
			temp_tetri[i][j] = tetri[i][j];
	}
}

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
	{
		printf("tetri %c == 0\n", 'A' + i);
		return (i);
	}
	put_tetri_in_square(tetri, square, i);
	printf("On a posey %c\n", 'A' + i);
	tetri_cpy[0] = tetri[i + 1][0];
	tetri_cpy[1] = tetri[i + 1][1];
	tetri_cpy[2] = tetri[i + 1][2];
	tetri_cpy[3] = tetri[i + 1][3];
	printf("On a copiey %c\n", 'A' + i + 1);
	printf("tetri_cpy[0] = %llu\n", tetri_cpy[0]);
	while (tetri[i + 1][0] != ~(0ULL) &&
			(ret = square_vs_tetri(square, tetri, i + 1)) < 27)
	{
		printf("ret = %d\n", ret);
		tetri[i + 1][0] = tetri_cpy[0];
		tetri[i + 1][1] = tetri_cpy[1];
		tetri[i + 1][2] = tetri_cpy[2];
		tetri[i + 1][3] = tetri_cpy[3];
		printf("On a reinit %c\n", 'A' + i + 1);
		printf("%c = %llu\n", 'A' + i + 1, tetri[i + 1][0]);
		remove_tetri_from_square(tetri, square, i);
		printf("On a sup %c du carrey\n", 'A' + i);
		shift_by_one(tetri, i);
		while ((tetri[i][0] & square[0]) || (tetri[i][1] & square[1]) ||
				(tetri[i][2] & square[2]) || (tetri[i][3] & square[3]))
			shift_by_one(tetri, i);
		printf("On a shiftey %c par au moins 1\n", 'A' + i);
		put_tetri_in_square(tetri, square, i);
		printf("On a posey %c\n", 'A' + i);
	}
	//	if ((!(tetri[i][0] & square[0])) && (!(tetri[i][1] & square[1])) &&
	//			(!(tetri[i][2] & square[2])) && (!(tetri[i][3] & square[3])))
	//	{
		put_tetri_in_square(tetri, square, i);
	//	}
	printf("Yoooo On a posey %c\n", 'A' + i);
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
	size = 3;
	i = -1;
	while (size)
	{
		j = 0;
		grid_init(square, size);
		printf("\033[31mReinitialisation grille (%d)\n", size);
		tetri_cpy(tetri, temp_tetri);
		i = square_vs_tetri(square, temp_tetri, j);
		printf("square_vs_tetri = %d\nEnvoi au displayer\n\033[0m",  i);
		fillit_displayer(temp_tetri, size, (i > 27) ? i - 27: i);
		size++;
		if (i > 27)
			break;
	}
	return (1);
}