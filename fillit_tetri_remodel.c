/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit_tetri_remodel.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amehmeto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/21 07:31:05 by amehmeto          #+#    #+#             */
/*   Updated: 2017/01/22 03:21:41 by amehmeto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Libft/libft.h"
#include "fillit.h"

static int		line_empty(const char *s)
{
	int		i;

	i = 0;
	while (s[i] != '\n')
	{
		if (s[i] == '.')
			i++;
		else
			return (0);
	}
	return (1);
}

static int		col_empty(const char *s)
{
	int		i;
	int		n;

	i = 0;
	n = 4;
	while (s[i] == '.' && n--)
		i += 5;
	if (n)
		return (0);
	return (1);
}

static void		col_mover(char *s)
{
	char	temp2[20];
	int		i;
	int		j;

	while (col_empty(s))
	{
		j = -5;
		while (j + 5 < 3)
		{
			i = j;
			while ((i += 5) < 20)
				ft_memcpy(&temp2[i], &s[i], 1);
			i = j;
			while ((i += 5) < 20)
				ft_memcpy(&s[i], &s[i + 1], 1);
			i = j;
			while ((i += 5) < 20)
				ft_memcpy(&s[i + 1], &temp2[i], 1);
			j++;
		}
	}
}

void			fillit_tetri_remodel(char *s)
{
	char	temp[5];

	while (line_empty(s))
	{
		ft_memcpy(temp, s, 5);
		ft_memcpy(&s[0], &s[5], 15);
		ft_memcpy(&s[15], temp, 5);
	}
	col_mover(s);
}
