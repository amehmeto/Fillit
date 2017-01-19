/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amehmeto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/16 21:56:01 by amehmeto          #+#    #+#             */
/*   Updated: 2017/01/19 08:00:52 by amehmeto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Libft/libft.h"
#include "fillit.h"

int		main(int ac, char **av)
{
	int		a;

	if (ac != 2)
	{
		ft_putstr("usage: ./fillit source_file.fillit\n");
		return (0);
	}
	if ((a = fillit_is_sample_valid(av[1])))
	{
//		ft_putstr("sample is not valid\n");
		printf("sample is not valid (%d)\n", a);
		return (0);
	}
	return (0);
}
