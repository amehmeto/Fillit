/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit_encoder.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amehmeto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/24 14:45:52 by amehmeto          #+#    #+#             */
/*   Updated: 2017/03/31 11:19:39 by amehmeto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Libft/libft.h"
#include "fillit.h"

#define BUFF_SIZE 21

/*
 * **************************************************************************
*/

static void			struct_init(unsigned long long tetri[27][4], int j)
{
	tetri[j][0] = 0;
	tetri[j][1] = 0;
	tetri[j][2] = 0;
	tetri[j][3] = 0;
}

static void			fillit_tetri_remodel(unsigned long long tetri[27][4], int j)
{
	while (tetri[j][0] < 0x1000000000000)
		tetri[j][0] <<= 16;
	while (!(tetri[j][0] & 0x8000800080008000))
		tetri[j][0] <<= 1;
}

void				fillit_encoder(int fd, unsigned long long tetri[27][4])
{
	char				buffer[BUFF_SIZE + 1];
	unsigned long long	marker;
	ssize_t				ret;
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
				tetri[j][0] |= marker;
			if (buffer[i] != '\n')
				marker >>= 1;
			else
				marker >>= 12;
		}
		fillit_tetri_remodel(tetri, j);
	}
	tetri[++j][0] = ~(0ULL);
}
