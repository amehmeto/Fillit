/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit_resolver_annex.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amehmeto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/06 04:09:35 by amehmeto          #+#    #+#             */
/*   Updated: 2017/04/06 05:51:45 by amehmeto         ###   ########.fr       */
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

void			grid_init(unsigned long long square[4], int size)
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
