/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amehmeto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/16 21:56:01 by amehmeto          #+#    #+#             */
/*   Updated: 2017/04/07 00:34:46 by amehmeto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

int					main(int ac, char **av)
{
	unsigned long long		tetri[27][4];
	int						a;
	int						fd;

	if (ac != 2)
	{
		ft_putstr("usage: ./fillit source_file.fillit\n");
		return (0);
	}
	if ((fd = open(av[1], O_RDWR)) == -1)
		ft_putstr("open error\n");
	if ((a = fillit_is_sample_valid(fd)))
	{
		ft_putstr("error\n");
	//	printf("sample is not valid (%d)\n", a);
		return (0);
	}
	if ((fd = open(av[1], O_RDWR)) == -1)
		ft_putstr("open error\n");
	fillit_encoder(fd, tetri);
	fillit_resolver(tetri);
	return (0);
}
