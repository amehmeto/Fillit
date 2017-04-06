/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit_resolver.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amehmeto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/25 21:26:50 by amehmeto          #+#    #+#             */
/*   Updated: 2017/04/04 20:27:44 by amehmeto         ###   ########.fr       */
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

	size_cpy = size;
	i = -1;
	j = 0;
	while (++i <= size)
	{
		if (i >= j * 4 && i <= (j + 1) * 4)
			quartr_to_fill = &square[j++];
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
	while (++j < 4)
		square[j] = ~square[j];
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

static int		square_vs_tetri(unsigned long long square[4],
		unsigned long long tetri[27][4],
		int i)
{

	while ((tetri[i][0] & square[0]) || (tetri[i][1] & square[1]) ||
			(tetri[i][2] & square[2]) || (tetri[i][3] & square[3]))
	{
		printf("Decalage du tetri %c\n", 'A' + i);
		shift_by_one(tetri, i);
	}
	if (!tetri[i][0] && !tetri[i][1] && !tetri[i][2] && !tetri[i][3])
	{
		printf("tetri %c == 0\n", 'A' + i);
		return (i);
	}
	if ((!(tetri[i][0] & square[0])) && (!(tetri[i][1] & square[1])) &&
			(!(tetri[i][2] & square[2])) && (!(tetri[i][3] & square[3])))
	{
		square[0] ^= tetri[i][0];
		square[1] ^= tetri[i][1];
		square[2] ^= tetri[i][2];
		square[3] ^= tetri[i][3];
		printf("On a posey %c\n", 'A' + i);
		if (tetri[i + 1][0] != ~(0ULL))
		{
			printf("tetri %c != ~(0ULL)\n", 'A' + i + 1);
			return (square_vs_tetri(square, tetri, i+1));
		}
		printf("wesh\n");
		printf("tetri[i + 1][0] == %llu\n", tetri[i + 1][0]);
	}
	return (-2);
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
	i = -2;
	while (size < 6 && (i == -2 || i >= 0))
	{
		j = 0;
		grid_init(square, size);
		printf("\033[31mReinitialisation grille (%d)\n", size);
		tetri_cpy(tetri, temp_tetri);
		i = square_vs_tetri(square, temp_tetri, j);
		printf("square_vs_tetri = %d\nEnvoi au displayer\n\033[0m", i);
		fillit_displayer(temp_tetri, size, i);
		size++;
		if (i == -3)
			break;
	}
	return (1);
}
