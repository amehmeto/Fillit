/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit_resolver.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amehmeto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/25 21:26:50 by amehmeto          #+#    #+#             */
/*   Updated: 2017/03/29 03:42:17 by amehmeto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

/*
 * **************************************************************************
*/

static void	delete_excess(struct mask *tetri, int i)
{
	while (tetri[i++].a)
		tetri[i - 1].a = 0;
}

/*
 * **************************************************************************
*/

void		grid_init(struct mask *square, int size)
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
			quartr_to_fill = &square->a;
		if (i > 4 && i <= 8)
			quartr_to_fill = &square->b;
		if (i > 8 && i <= 12)
			quartr_to_fill = &square->c;
		if (i > 12 && i <= 16)
			quartr_to_fill = &square->d;
		*quartr_to_fill = *quartr_to_fill >> 16;
		marker = 0x8000000000000000;
		size_cpy = size;
		while (size_cpy--)
		{
			*quartr_to_fill = *quartr_to_fill ^ marker;
			marker = marker >> 1;
		}
	}
	square->a = ~square->a;
	square->b = ~square->b;
	square->c = ~square->c;
	square->d = ~square->d;
}

static int	square_vs_tetri(struct mask *square, struct mask *tetri, int size)
{
	int				i;

	i = -1;
	while (++i <= 26)
	{
		while ((tetri[i].a & square->a)
				&& !(tetri[i].a & 1))
			tetri[i].a = tetri[i].a >> 1;
		if (!(tetri[i].a & square->a))
			square->a = square->a ^ tetri[i].a;
		else
			return (i);
		printf("\nSquare %d\n", i);
		fillit_displayer(tetri, size);
	}
	return (0);
}

void		fillit_resolver(struct mask *tetri)
{
	struct mask			square;
	int					size;
	int					i;

	square.a = 0;
	square.b = 0;
	square.c = 0;
	square.d = 0;
	size = 14;
	grid_init(&square, size);
	i = square_vs_tetri(&square, tetri, size);
	delete_excess(tetri, i);
	printf("\nResultat final\n");
	fillit_displayer(tetri, size);
/*
** while (square_vs_tetri(&square, tetri) && size < 16)
** {
** 		printf("\nsize = %d\n", size);
** 		square.a = 0;
** 		square.b = 0;
** 		square.c = 0;
** 		square.d = 0;
** 		grid_init(&square, ++size);
** 		}
*/
	(void)tetri;
}
