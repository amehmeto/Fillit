/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amehmeto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/16 21:56:01 by amehmeto          #+#    #+#             */
/*   Updated: 2017/03/27 20:49:41 by amehmeto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

int					main(int ac, char **av)
{
	struct mask		tetri[26];
	int				a;
	int				fd;
	int				i;

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
	i = -1;
//	while (tetri[++i].first_quartr)
//		printf("Tetri n* %d = %llu\n", i, tetri[i].first_quartr);
	fillit_resolver(tetri);
	if (fillit_displayer(tetri, 4))
		ft_putstr("ca marche pas\n");
	return (0);
}
