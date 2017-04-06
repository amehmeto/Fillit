/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit_displayer_no_color.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amehmeto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/27 23:38:16 by amehmeto          #+#    #+#             */
/*   Updated: 2017/04/06 21:30:13 by amehmeto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

static void		delete_excess(unsigned long long t[27][4], int i)
{
	if (i > 27)
		i = 26;
	t[i][0] = ~(0ULL);
	t[i][1] = ~(0ULL);
	t[i][2] = ~(0ULL);
	t[i][3] = ~(0ULL);
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

static void		t_printer(unsigned long long t[27][4], int size, char *r)
{
	unsigned long long		printer;
	int						i;
	int						j;
	int						k;

	k = -1;
	while (++k < 4)
	{
		j = -1;
		while (t[++j][k] != ~(0ULL))
		{
			printer = 0x8000000000000000;
			i = size * 4 * k + (k * 4) - 1;
			while (r[++i])
			{
				if (r[i] != '\n')
					if (t[j][k] & printer)
						r[i] = 'A' + (char)j;
				printer >>= 1;
				if (r[i] == '\n')
					printer >>= (15 - size);
			}
		}
	}
}

int				fillit_displayer(unsigned long long t[27][4], int size, int i)
{
	char					*r;

	if (!(r = (char*)malloc(sizeof(char) * 273)))
		return (1);
	points_initializer(size, r);
	delete_excess(t, i);
	t_printer(t, size, r);
	ft_putstr(r);
	free(r);
	return (0);
}
