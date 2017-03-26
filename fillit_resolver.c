/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit_resolver.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amehmeto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/25 21:26:50 by amehmeto          #+#    #+#             */
/*   Updated: 2017/03/26 22:29:10 by amehmeto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

static void				grid_init(struct mask *square, int size)
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
			quartr_to_fill = &square->third_quartr;
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

void					fillit_resolver(struct mask *tetri)
{
	struct mask			square;
	int					size;

	square.first_quartr = 0;
	square.secnd_quartr = 0;
	square.third_quartr = 0;
	square.forth_quartr = 0;
	(void)tetri;
	size = 10;
	grid_init(&square, size);
	printf("1st quartr = %llu\n", square.first_quartr);
	printf("2nd quartr = %llu\n", square.secnd_quartr);
	printf("3rd quartr = %llu\n", square.third_quartr);
	printf("4th quartr = %llu\n", square.forth_quartr);
}
