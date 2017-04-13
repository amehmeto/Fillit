/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit_checker.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amehmeto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/13 23:16:48 by amehmeto          #+#    #+#             */
/*   Updated: 2017/04/13 23:36:21 by amehmeto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

#define BUFF_SIZE 21

/*
** ************************************************************************** **
*/

static int		ft_links_counter(const char *s, int i)
{
	int		links;

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

static int		ft_only_sharps_and_dots(char *s)
{
	int		links;
	int		i;

	i = 0;
	links = 0;
	while (s[i])
	{
		if (s[i] != '.' && s[i] != '#' && s[i] != '\n')
			return (1);
		if (s[i] == '#')
		{
			if (!(ft_links_counter(s, i)))
				return (1);
			links += ft_links_counter(s, i);
		}
		i++;
	}
	if (links != 6 && links != 8)
		return (1);
	return (0);
}

static int		ft_sharps_counter(const char *s)
{
	int		counter;

	counter = 0;
	while (*s)
	{
		if (*s == '#')
			counter++;
		s++;
	}
	return (counter);
}

static int		ft_blackslahes_wrong(const char *s, ssize_t ret)
{
	int		i;

	i = -1;
	if (++i == 0 && s[i] == '\n')
		return (1);
	while (++i < 20)
	{
		if (!s[i])
			return (2);
		if ((i + 1) % 5)
		{
			if (s[i] == '\n')
				return (3);
		}
		else
		{
			if (s[i] != '\n')
				return (4);
		}
	}
	if (s[20] && ret == 20)
		return (6);
	if (s[20] && s[i] != '\n')
		return (5);
	return (0);
}

int				fillit_checker(char buffer[BUFF_SIZE + 1], ssize_t ret)
{
	buffer[ret] = '\0';
	if (ft_only_sharps_and_dots(buffer))
		return (10);
	if (ft_blackslahes_wrong(buffer, ret))
		return (30);
	if (ft_sharps_counter(buffer) != 4)
		return (40);
	return (0);
}
