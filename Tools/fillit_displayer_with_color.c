/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit_displayer_with_color.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amehmeto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/27 23:35:33 by amehmeto          #+#    #+#             */
/*   Updated: 2017/04/06 02:29:31 by amehmeto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

static void		delete_excess(unsigned long long tetri[27][4], int i)
{
	if (i > 27)
		i = 26;
	tetri[i][0] = ~(0ULL);
	tetri[i][1] = ~(0ULL);
	tetri[i][2] = ~(0ULL);
	tetri[i][3] = ~(0ULL);
}

static void		points_initializer(int size, char *r)
{
	int		i;
	int		j;
	int		k;

	i = 0;
	j = size;
	while (j--)
	{
		k = size;
		while (k--)
			r[i++] = '.';
		r[i++] = '\n';
	}
	r[i] = '\0';
}

static void		tetri_printer(unsigned long long tetri[27][4], int size, char *r)
{
	unsigned long long		printer;
	int						i;
	int						j;
	int						k;

	k = -1;
	while (++k < 4)
	{
		j = -1;
		while (tetri[++j][k] != ~(0ULL))
		{
			printer = 0x8000000000000000;
			i = size * 4 * k + (k * 4) - 1;
			while (r[++i])
			{
				if (r[i] != '\n')
				{
					if (tetri[j][k] & printer)
						r[i] = 'A' + (char)j;
					printer >>= 1;
				}
				else
					printer >>= (16 - size);
			}
		}
	}
}

int			fillit_displayer(unsigned long long tetri[27][4], int size, int j)
{
//	unsigned long long		temp_tetri[27][4];
	char					*ret1;
	char					*ret2;
	char					*r;
	int						i;
	int						k;
	int						l;

	if (!(r = (char*)malloc(sizeof(char) * 273)))
		return (1);
	points_initializer(size, r);
/*	k = -1;
	while (++k < 27)
	{
		l = -1;
		while (++l < 4)
			printf("tetri[%d][%d] = %llu\n", k, l, tetri[k][l]);
	}*/
	delete_excess(tetri, j);
	tetri_printer(tetri, size, r);
	system("clear");
	printf("Size = %d\nretour = %d\n\n", size, j);
	ret1 = NULL;
	ret2 = NULL;
	i = -1;
	while (r[++i])
	{
		if (ft_isalpha(r[i]))
		{
			ret1 = ft_itoa(30 + (r[i] % 7));
			ret2 = ft_strjoin(ret1, "m");
			ret1 = ft_strjoin("\033[", ret2);
			free(ret2);
			ft_putstr(ret1);
			free(ret1);
		}
		ft_putchar(r[i]);
		ft_putstr("\033[0m");
	}
	free(r);
	usleep(10);
	return (0);
}
