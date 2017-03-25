/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit_encoder.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amehmeto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/24 14:45:52 by amehmeto          #+#    #+#             */
/*   Updated: 2017/03/25 21:36:59 by amehmeto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Libft/libft.h"
#include "fillit.h"

#define BUFF_SIZE 21

/*
 * **************************************************************************
*/

void					struct_init(struct mask *tetri, int j)
{
	tetri[j].first_quartr = 0;
	tetri[j].secnd_quartr = 0;
	tetri[j].third_quartr = 0;
	tetri[j].forth_quartr = 0;
}

void					fillit_encoder(int fd, struct mask *tetri)
{
	char				buffer[BUFF_SIZE + 1];
	unsigned long long	marker;
	int					ret;
	int					i;
	int					j;

	j = -1;
	while ((ret = read(fd, buffer, BUFF_SIZE)) == 21 || ret == 20)
	{
		buffer[ret] = '\0';
		struct_init(tetri, ++j);
		marker = 0x8000000000000000;
		i = -1;
		while (buffer[++i])
		{
			if (buffer[i] == '#')
				tetri[j].first_quartr = tetri[j].first_quartr | marker;
			if (buffer[i] != '\n')
				marker = marker >> 1;
			else
				marker = marker >> 12;
		}
	}
	tetri[++j].first_quartr = 0;
}
