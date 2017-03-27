/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit_resolver.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amehmeto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/25 21:26:50 by amehmeto          #+#    #+#             */
/*   Updated: 2017/03/27 05:18:52 by amehmeto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

void				grid_init(struct mask *square, int size)
{
	unsigned long long	*quartr_to_fill;
	unsigned long long	marker;
	int					size_cpy;
	int					i;

	size_cpy = size;
	i = -1;
	while (++i <= size)
	{
		if (i <= 4)
			quartr_to_fill = &square->first_quartr;
		if (i > 4 && i <= 8)
			quartr_to_fill = &square->secnd_quartr;
		if (i > 8 && i <= 12)
			quartr_to_fill = &square->third_quartr;
		if (i > 12 && i <= 16)
			quartr_to_fill = &square->forth_quartr;
		*quartr_to_fill = *quartr_to_fill >> 16;
		marker = 0x8000000000000000;
		size_cpy = size;
		while (size_cpy--)
		{
			*quartr_to_fill = *quartr_to_fill ^ marker;
			marker = marker >> 1;
		}
	}
	square->first_quartr = ~square->first_quartr;
	square->secnd_quartr = ~square->secnd_quartr;
	square->third_quartr = ~square->third_quartr;
	square->forth_quartr = ~square->forth_quartr;
}

static int				square_vs_tetri(struct mask *square, struct mask *tetri)
{
	int		i;

	i = -1;
	while (++i <= 26)
	{
		while ((tetri[i].first_quartr & square->first_quartr)
				&& !(tetri[i].first_quartr & 1))
			tetri[i].first_quartr = tetri[i].first_quartr >> 1;
		if (!(tetri[i].first_quartr & square->first_quartr))
			square->first_quartr = square->first_quartr ^ tetri[i].first_quartr;
		else
			return (i + 1);
		printf("SQUARE %d  = %llu\n", i, square->first_quartr);
	}
	return (0);
}

void					fillit_resolver(struct mask *tetri)
{
	struct mask			square;
	int					size;

	square.first_quartr = 0;
	square.secnd_quartr = 0;
	square.third_quartr = 0;
	square.forth_quartr = 0;
	size = 14;
	grid_init(&square, size);
	printf("1st quartr = %llu\n", square.first_quartr);
	printf("2nd quartr = %llu\n", square.secnd_quartr);
	printf("3rd quartr = %llu\n", square.third_quartr);
	printf("4th quartr = %llu\n\n", square.forth_quartr);
	while (square_vs_tetri(&square, tetri) && size < 16)
	{
		printf("\nsize = %d\n", size);
		square.first_quartr = 0;
		square.secnd_quartr = 0;
		square.third_quartr = 0;
		square.forth_quartr = 0;
		grid_init(&square, ++size);
	}
}
