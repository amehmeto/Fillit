/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit_displayer.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amehmeto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/27 02:37:48 by amehmeto          #+#    #+#             */
/*   Updated: 2017/03/27 22:54:51 by amehmeto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

int		fillit_displayer(struct mask *tetri, int size)
{
	unsigned long long		printer;
	struct mask				grid;
	int						i;
	int						j;
	int						k;
	char					*r;

	(void)tetri;
	grid.first_quartr = 0;
	grid.secnd_quartr = 0;
	grid.third_quartr = 0;
	grid.forth_quartr = 0;
	if (!(r = (char*)malloc(sizeof(char) * 256)))
		return (1);
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


	j = -1;
	while (tetri[++j].first_quartr)
	{
		ft_putstr("\033[0m");
		printf("Impression du tetri %c\n", 'A' + j);
		i = -1;
		printer = 0x8000000000000000;
		while (r[++i])
		{
			if (r[i] != '\n')
			{
				if (tetri[j].first_quartr & printer)
					r[i] = 'A' + j;
				if (ft_isalpha(r[i]))
					ft_putstr(ft_strjoin("\033[", ft_strjoin(ft_itoa(30 + (j % 7)), "m")));
				else
					ft_putstr("\033[0m");
				printer = printer >> 1;
				ft_putchar(r[i]);
			}
			else
			{
				ft_putstr("\033[0m");
				ft_putchar(r[i]);
				printer = printer >> (16 - size);
			}
		}
	}
	printf("\nResultat final :\n");
	i = -1;
	while (r[++i])
	{
		if (ft_isalpha(r[i]))
			ft_putstr(ft_strjoin("\033[", ft_strjoin(ft_itoa(30 + (r[i] % 7)), "m")));
		ft_putchar(r[i]);
		ft_putstr("\033[0m");
	}
	ft_putstr("\033[0m");
	return (0);
}
