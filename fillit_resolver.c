/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit_resolver.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amehmeto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/25 21:26:50 by amehmeto          #+#    #+#             */
/*   Updated: 2017/03/31 13:25:13 by amehmeto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

/*
 * **************************************************************************
 */

//static void	delete_excess(unsigned long long tetri[27][4], int i)
//{
//	if (i == -1)
//		i = 26;
//	tetri[i][0] = ~(0ULL);
//	tetri[i][1] = ~(0ULL);
//	tetri[i][2] = ~(0ULL);
//	tetri[i][3] = ~(0ULL);
//}

/*
 * **************************************************************************
 */

void		grid_init(unsigned long long square[4], int size)
{
	unsigned long long	*quartr_to_fill;
	unsigned long long	marker;
	int					size_cpy;
	int					i;

	quartr_to_fill = NULL;
	size_cpy = size;
	i = -1;
	while (++i <= size)
	{
		if (i <= 4)
			quartr_to_fill = &square[0];
		if (i > 4 && i <= 8)
			quartr_to_fill = &square[1];
		if (i > 8 && i <= 12)
			quartr_to_fill = &square[2];
		if (i > 12 && i <= 16)
			quartr_to_fill = &square[3];
		*quartr_to_fill >>= 16;
		marker = 0x8000000000000000;
		size_cpy = size;
		while (size_cpy--)
		{
			*quartr_to_fill ^= marker;
			marker >>= 1;
		}
	}
	square[0] = ~square[0];
	square[1] = ~square[1];
	square[2] = ~square[2];
	square[3] = ~square[3];
}

static int	square_vs_tetri(unsigned long long square[4], 
							unsigned long long tetri[27][4], int size)
{
	unsigned long long		marker;
	int						i;

	marker = 0x8000000000000000;
	(void)size;
	i = -1;
	while (++i <= 25)
	{
		while ((tetri[i][0] & square[0]) || (tetri[i][1] & square[1]) ||
				(tetri[i][2] & square[2]) || (tetri[i][3] & square[3]))
		{
			tetri[i][3] >>= 1;
			tetri[i][3] |= ((tetri[i][2] & 1) << 63);
			tetri[i][2] >>= 1;
			tetri[i][2] |= ((tetri[i][1] & 1) << 63);
			tetri[i][1] >>= 1;
			tetri[i][1] |= ((tetri[i][0] & 1) << 63);
			tetri[i][0] >>= 1;
			if (!(tetri[i][0]) && !(tetri[i][1]) && !(tetri[i][2]) && !(tetri[i][3]))
				break ;
		}
		if (!tetri[i][0] && !tetri[i][1] && !tetri[i][2] && !tetri[i][3])
			return (i);
		if ((!(tetri[i][0] & square[0])) && (!(tetri[i][1] & square[1])) &&
				(!(tetri[i][2] & square[2])) && (!(tetri[i][3] & square[3])))
		{
			square[0] ^= tetri[i][0];
			square[1] ^= tetri[i][1];
			square[2] ^= tetri[i][2];
			square[3] ^= tetri[i][3];
		}
	}
	return (-1);
}

void		fillit_resolver(unsigned long long tetri[27][4])
{
	unsigned long long		square[4];
	int						size;
	int						i;

	square[0] = 0;
	square[1] = 0;
	square[2] = 0;
	square[3] = 0;
	size = 15;
	grid_init(square, size);
	i = square_vs_tetri(square, tetri, size);
	while (size < 16)
	{
		printf("Size %d\n\n", size);
		system("clear");
		fillit_displayer(tetri, size, i);
		sleep(1);
		size++;
	}
}
