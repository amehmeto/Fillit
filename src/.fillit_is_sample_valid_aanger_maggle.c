/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit_is_sample_valid_aanger_maggle.c             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amehmeto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/07 02:01:04 by amehmeto          #+#    #+#             */
/*   Updated: 2017/04/07 02:01:40 by amehmeto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

#define BUFF_SIZE 21

static int            ft_links_counter(const char *s, int i)
{
	int        links;

	links = 0;
	if (s[i - 1] == '#')
		links++;
	if (s[i + 1] == '#')
		links++;
	if (s[i - 5] == '#')
		links++;
	if (s[i + 5] == '#')
		links++;
	return (links);
}

int                    fillit_is_sample_valid(int fd)
{
	char			buffer[BUFF_SIZE + 1];
	ssize_t        ret;
	int            i;
	int            count;

	i = 0;
	count = 0;
	while ((ret = read(fd, buffer, BUFF_SIZE)) == 21 || ret == 20)
	{
		while (i < 22)
		{
			if (buffer[i] != '.' && buffer[i] != '#' && buffer[i] != '\n')
				return (1);
			if ((i % 4) != '\n')
				return (1);
			if (i == '#')
				count += ft_links_counter(buffer, i);
			i++;
		}
		if (count != 6 && count != 8)
			return (1);
		i = 0;
	}
	return (0);
}
