/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit_is_sample_valid.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amehmeto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/16 22:32:44 by amehmeto          #+#    #+#             */
/*   Updated: 2017/04/07 00:52:42 by amehmeto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

#define BUFF_SIZE 21

/*
** ************************************************************************** **
*/

static size_t		ft_strlen_mod(const char *s)
{
	size_t		i;

	i = 0;
	while (s[i] != '\n')
		i++;
	return (i);
}

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
/*
static int			ft_only_sharps_and_dots(char *s)
{
	int		links;
	int		i;

	i = 0;
	links = 0;
	while (s[i])
	{
		if (((!(i + 1) % 5) || (!(i + 1) % 21)) && s[i] != '\n')
		{
			printf("i = %d \t s[i] = %c\n", );
			return (1);
		}
		else
			if (s[i] != '.' && s[i] != '#')
				return (1);
		
		if (s[i] == '#')
			links += ft_links_counter(s, i); 
		i++;
	}
	if (links != 6 && links != 8)
		return (1);
	return (0);
}
*/
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

/*
** ************************************************************************** **
*/

int					fillit_is_sample_valid(int fd)
{
	char		buffer[BUFF_SIZE + 1];
	ssize_t		ret;
	int			i;
	int			n;
	int			a;

	while ((ret = read(fd, buffer, BUFF_SIZE)) == 21 || ret == 20)
	{
		buffer[ret] = '\0';
	//	if ((a = ft_only_sharps_and_dots(buffer)))
	//		return (10);
		if (ft_sharp_counter(buffer) != 4)
			return (20);
		i = 0;
		if (ret == 21 || ret == 20)
		{
			while (buffer[i])
			{
				if (ft_strlen_mod(&buffer[i]) == 4)
				{
					n = 4;
					while (n--)
					{
						if (ft_strlen_mod(&buffer[i]) == 4
								&& ft_strlen_mod(&buffer[i + 4]) == 0)
							i += 5;
						else
							return (30 + n);
					}
				}
				else
					return (40);
				i++;
			}
		}
	}
	buffer[ret] = '\0';
	if (close(fd) == -1)
		ft_putstr("close error\n");
	return (0);
}
