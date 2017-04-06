/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit_resolver.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amehmeto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/06 20:46:57 by amehmeto          #+#    #+#             */
/*   Updated: 2017/04/06 20:46:59 by amehmeto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

static void		quarter_filler(int size, unsigned long long *quartr_to_fill)
{
	unsigned long long	marker;
	int					size_cpy;

	size_cpy = size;
	marker = 0x8000000000000000;
	*quartr_to_fill >>= 16;
	size_cpy = size;
	while (size_cpy--)
	{
		*quartr_to_fill ^= marker;
		marker >>= 1;
	}
}

static void		grid_init(unsigned long long square[4], int size)
{
	unsigned long long	*quartr_to_fill;
	int					i;
	int					j;

	quartr_to_fill = NULL;
	i = -1;
	j = 0;
	while (++i < size)
	{
		if (i >= j * 4 && i < (j + 1) * 4)
		{
			quartr_to_fill = &square[j++];
			*quartr_to_fill = 0;
		}
		quarter_filler(size, quartr_to_fill);
	}
	j = -1;
	while (++j < 4 && square[j] != ~(0ULL))
		square[j] = ~square[j];
}

/*
** **************************************************************************
*/

static void		t_cpy(unsigned long long t[27][4],
						unsigned long long temp_t[27][4])
{
	int		i;
	int		j;

	i = -1;
	while (++i < 27)
	{
		j = -1;
		while (++j < 4)
			temp_t[i][j] = t[i][j];
	}
}

int				fillit_resolver(unsigned long long t[27][4])
{
	unsigned long long		temp_t[27][4];
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
		t_cpy(t, temp_t);
		i = square_vs_t(square, temp_t, j);
		size++;
		if (i > 27)
			break ;
	}
	fillit_displayer(temp_t, size - 1, (i > 27) ? i - 27 : i);
	return (1);
}
