/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit_resolver.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amehmeto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/25 21:26:50 by amehmeto          #+#    #+#             */
/*   Updated: 2017/03/26 04:03:48 by amehmeto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

static void		grid_init(struct mask square, int size)
{
	unsigned long long 	eraser;
	int					size_cpy;
	int					size_reminder;
	int					compensator;

	eraser = 0x8000000000000000;
	size_cpy = size;
	size_reminder = size;
	printf("size = %d, size_cpy = %d\n", size, size_cpy);
	while (size--)
	{
		size_cpy = size_reminder;
		compensator = 0;
		while (size_cpy-- > 0)
		{
			square.first_quartr = square.first_quartr ^ eraser;
			eraser = eraser >> 16;
			compensator++;
			printf("eraser = eraser >> 16 --> %llu\n", square.first_quartr);
			printf("size_cpy = %d    | compensator = %d\n", size_cpy, compensator);
		}
		eraser = eraser << (compensator * 16 - 1);
		printf("eraser = eraser << (compensator * 16 - 1) ====> %llu\n\n", eraser);
	}
	printf("Square = %llu\n", square.first_quartr);
}

void			fillit_resolver(struct mask *tetri)
{
	struct mask		square;
	int				size;

	square.first_quartr = 0xFFFFFFFFFFFFFFFF;
	square.secnd_quartr = 0xFFFFFFFFFFFFFFFF;
	square.third_quartr = 0xFFFFFFFFFFFFFFFF;
	square.forth_quartr	= 0xFFFFFFFFFFFFFFFF;
	(void)tetri;
	size = 4;
	grid_init(square, size);
	printf("Square = %llu\n", square.first_quartr);
}
