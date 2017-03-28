/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tetri_printer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amehmeto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/27 23:33:09 by amehmeto          #+#    #+#             */
/*   Updated: 2017/03/28 05:11:57 by amehmeto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

static int		tetri_displayer(struct mask *tetri, int size)
{
	unsigned long long		printer;
	int						i;
	int						j;
	int						k;
	char					*r;

	if (!(r = (char*)malloc(sizeof(char) * 3 * 256)))
		return (1);
	j = -1;
	i = 0;
	while (tetri[++j].first_quartr)
	{
		printer = 0x8000000000000000;
		k = 0;
		while (++k <= 16)
		{
			if (tetri[j].first_quartr & printer)
				r[i] = 'A' + j;
			else
				r[i] = '.';
			if (!(k % 4))
			{
				r[++i] = '\n';
				printer = printer >> (16 - size);
			}
			i++;
			printer = printer >> 1;
		}
		r[i++] = '\n';
	}
	r[++i] = '\0';
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

int				main(int ac, char **av)
{
	struct mask		tetri[26];
	int				a;
	int				fd;
	int				i;

	i = -1;
	if (ac != 2)
	{
		ft_putstr("usage: ./fillit source_file.fillit\n");
		return (0);
	}
	if ((fd = open(av[1], O_RDWR)) == -1)
		ft_putstr("open error\n");
	if ((a = fillit_is_sample_valid(fd)))
	{
		printf("sample is not valid (%d)\n", a);
		return (0);
	}
	if ((fd = open(av[1], O_RDWR)) == -1)
		ft_putstr("open error\n");
	fillit_encoder(fd, tetri);
	tetri_displayer(tetri, 4);
	return (0);
}
