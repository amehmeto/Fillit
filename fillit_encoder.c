/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit_encoder.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amehmeto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/24 14:45:52 by amehmeto          #+#    #+#             */
/*   Updated: 2017/04/06 19:42:00 by amehmeto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Libft/libft.h"
#include "fillit.h"

#define BUFF_SIZE 21

/*
** **************************************************************************
*/

static void			struct_init(unsigned long long t[27][4], int j)
{
	t[j][0] = 0;
	t[j][1] = 0;
	t[j][2] = 0;
	t[j][3] = 0;
}

static void			fillit_t_remodel(unsigned long long t[27][4], int j)
{
	while (t[j][0] < 0x1000000000000)
		t[j][0] <<= 16;
	while (!(t[j][0] & 0x8000800080008000))
		t[j][0] <<= 1;
}

void				fillit_encoder(int fd, unsigned long long t[27][4])
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
		struct_init(t, ++j);
		marker = 0x8000000000000000;
		i = -1;
		while (buffer[++i])
		{
			if (buffer[i] == '#')
				t[j][0] |= marker;
			if (buffer[i] != '\n')
				marker >>= 1;
			else
				marker >>= 12;
		}
		fillit_t_remodel(t, j);
	}
	t[++j][0] = ~(0ULL);
}
