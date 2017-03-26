/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit_resolver.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amehmeto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/25 21:26:50 by amehmeto          #+#    #+#             */
/*   Updated: 2017/03/26 21:26:03 by amehmeto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

static void		grid_init(struct mask square, int size)
{
	unsigned long long 	marker;
	int					size_cpy;
	int					size_reminder;

	size_cpy = size;
	size_reminder = size;
	printf("size = %d, size_cpy = %d\n", size, size_cpy);
	printf("SQUARE =====> %llu\n", square.first_quartr);
	while (size--)
	{
		marker = 0x8000000000000000;
		size_cpy = size_reminder;
		square.first_quartr = square.first_quartr >> 16;
		printf("SQUARE =====> %llu\n", square.first_quartr);
		while (size_cpy--)
		{
			printf("marker                   --> %llu\n", marker);
			square.first_quartr = square.first_quartr ^ marker;
			marker = marker >> 1;
			printf("square = square & marker --> %llu\n", square.first_quartr);
			printf("size_cpy = %d\n", size_cpy);
		}
	}
	printf("INVERTED SQUARE = %llu\n", square.first_quartr);
	square.first_quartr = ~square.first_quartr;
	printf("INVERTED SQUARE = %llu\n", square.first_quartr);
}

void			fillit_resolver(struct mask *tetri)
{
	struct mask		square;
	int				size;

	square.first_quartr = 0;
	square.secnd_quartr = 0;
	square.third_quartr = 0;
	square.forth_quartr	= 0;
	(void)tetri;
	size = 4;
	grid_init(square, size);
	printf("Square = %llu\n", square.first_quartr);
}
