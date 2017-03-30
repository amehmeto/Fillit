/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit_encoder.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amehmeto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/24 14:45:52 by amehmeto          #+#    #+#             */
/*   Updated: 2017/03/30 07:43:55 by amehmeto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Libft/libft.h"
#include "fillit.h"

#define BUFF_SIZE 21

/*
 * **************************************************************************
*/

static void				struct_init(struct mask *tetri, int j)
{
	tetri[j].a = 0;
	tetri[j].b = 0;
	tetri[j].c = 0;
	tetri[j].d = 0;
}

static void				fillit_tetri_remodel(struct mask *tetri, int j)
{
	while (tetri[j].a < 0x1000000000000)
		tetri[j].a = tetri[j].a << 16;
	while (!(tetri[j].a & 0x8000800080008000))
		tetri[j].a = tetri[j].a << 1;
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
				tetri[j].a = tetri[j].a | marker;
			if (buffer[i] != '\n')
				marker = marker >> 1;
			else
				marker = marker >> 12;
		}
		fillit_tetri_remodel(tetri, j);
	}
	tetri[++j].a = 0;
}
