/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit_is_sample_valid.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amehmeto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/16 22:32:44 by amehmeto          #+#    #+#             */
/*   Updated: 2017/04/07 03:59:11 by amehmeto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

#define BUFF_SIZE 21

/*
** ************************************************************************** **
*/

static int			ft_links_counter(const char *s, int i)
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

static int			ft_only_sharps_and_dots(char *s)
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
			links += ft_links_counter(s, i); 
		i++;
	}
	if (links != 6 && links != 8)
		return (1);
	return (0);
}

static size_t		ft_sharp_counter(const char *s)
{
	size_t		c;
	int			i;

	i = 0;
	c = 0;
	while (s[i])
		if (s[i++] == '#')
			c++;
	return (c);
}

static int			ft_blackslahes_wrong(const char *s, ssize_t ret)
{
	int		i;

	i = -1;
	if (++i == 0 && s[i] == '\n')
		return (1);
	while (++i < 20)
	{
		if (!s[i])
			return (2);
//		printf("i = %d \t s[i] = %c\n", i, s[i]);
//		printf("i + 1 modulo 5 = %d \n", ((i + 1) % 5));
		if ((i +1) % 5)
		{
			if (s[i] == '\n')
				return (3);
		}
		else
			if (s[i] != '\n')
				return (4);
	}
//	printf("s[20] = %c \t ret = %zd\n",s[20],ret );
	if (s[20] && ret == 20)
		return (6);
	if (s[20])
		if (s[i] != '\n')
			return (5);
	return (0);
}

/*
** ************************************************************************** **
*/

int					fillit_is_sample_valid(int fd)
{
	char		buffer[BUFF_SIZE + 1];
	ssize_t		ret;
	int			a;

	while ((ret = read(fd, buffer, BUFF_SIZE)) == 21)
	{
		buffer[ret] = '\0';
		if (ft_only_sharps_and_dots(buffer))
			return (10);
		if (ft_sharp_counter(buffer) != 4)
			return (20);
		if ((a = ft_blackslahes_wrong(buffer, ret)))
			return (30 + a);
	}
//	printf("ret = %zd\n", ret);
	if (ret == 0)
		return (1);
	if (ret == 20)
	{
		buffer[ret] = '\0';
		if (ft_only_sharps_and_dots(buffer))
			return (10);
		if (ft_sharp_counter(buffer) != 4)
			return (20);
		if ((a = ft_blackslahes_wrong(buffer, ret)))
			return (30 + a);
	}
	buffer[ret] = '\0';
//	printf("ret = %zd\n", ret);
	if (ret != 20 && ret != 21 && ret != 0)
		return (1);
	if (close(fd) == -1)
		ft_putstr("close error\n");
	return (0);
}
