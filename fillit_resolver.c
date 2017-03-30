/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit_resolver.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amehmeto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/25 21:26:50 by amehmeto          #+#    #+#             */
/*   Updated: 2017/03/30 09:18:02 by amehmeto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

/*
 * **************************************************************************
 */

static void	delete_excess(struct mask *tetri, int i)
{
	printf("##%d\n", i);
	if (i == -1)
		i = 26;
	tetri[i].a = ~(0ULL);
	tetri[i].b = ~(0ULL);
	tetri[i].c = ~(0ULL);
	tetri[i].d = ~(0ULL);
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
	unsigned long long		marker;
	int						i;

	(void)size;
	marker = 0x8000000000000000;
	i = -1;
	while (++i <= 25)
	{
		while ((tetri[i].a & square->a) ||
			(tetri[i].b & square->b) ||
			(tetri[i].c & square->c) ||
			(tetri[i].d & square->d))
		{		
			tetri[i].d >>= 1;
			tetri[i].d |= ((tetri[i].c & 1) << 63);
			tetri[i].c >>= 1;
			tetri[i].c |= ((tetri[i].b & 1) << 63);
			tetri[i].b >>= 1;
			tetri[i].b |= ((tetri[i].a & 1) << 63);
			tetri[i].a >>= 1;
		//	if (!(tetri[i].a & 1))
		//		tetri[i].a = tetri[i].a >> 1;
		//	else
		//	{
		//		tetri[i].b = tetri[i].b >> 1;
		//		tetri[i].b = tetri[i].b & marker;
		//		tetri[i].a = tetri[i].a >> 1;
		//	}
			if (tetri[i].a == 0 && tetri[i].b == 0 &&
				tetri[i].c == 0 && tetri[i].d == 0)
				break ;
		}

		if (!tetri[i].a && !tetri[i].b && !tetri[i].c && !tetri[i].d)
			return (i);
		if (!(tetri[i].a & square->a) &&
			!(tetri[i].b & square->b) &&
			!(tetri[i].c & square->c) &&
			!(tetri[i].d & square->d))
		{
			square->a = square->a ^ tetri[i].a;
			square->b ^= tetri[i].b;
			square->c ^= tetri[i].c;
			square->d ^= tetri[i].d;
		}
		//	printf("\nSquare %d\n", i);
		//	fillit_displayer(tetri, size);
	}
	return (-1);
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
	size = 16;
	grid_init(&square, size);
	i = square_vs_tetri(&square, tetri, size);
	delete_excess(tetri, i);
	while (size <= 16)
	{
		printf("Size %d\n", size);
		fillit_displayer(tetri, size);
		size++;
	}
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
