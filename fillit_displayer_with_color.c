/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit_displayer_with_color.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amehmeto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/27 23:35:33 by amehmeto          #+#    #+#             */
/*   Updated: 2017/03/28 05:40:40 by amehmeto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

void		points_initializer(int size, char *r)
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

int			fillit_displayer(struct mask *tetri, int size)
{
	unsigned long long		printer;
	int						i;
	int						j;
	char					*r;

	if (!(r = (char*)malloc(sizeof(char) * 2 * 256)))
		return (1);
	points_initializer(size, r);
	j = -1;
	while (tetri[++j].first_quartr)
	{
		printer = 0x8000000000000000;
		i = -1;
		while (r[++i])
		{
			if (r[i] != '\n')
			{
				if (tetri[j].first_quartr & printer)
					r[i] = 'A' + j;
				printer = printer >> 1;
			}
			else
				printer = printer >> (16 - size);
		}
	}
	i = -1;
	while (r[++i])
	{
		if (ft_isalpha(r[i]))
			ft_putstr(
				ft_strjoin("\033[", ft_strjoin(ft_itoa(30 + (r[i] % 7)), "m")));
		ft_putchar(r[i]);
		ft_putstr("\033[0m");
	}
	ft_putstr("\033[0m");
	return (0);
}
