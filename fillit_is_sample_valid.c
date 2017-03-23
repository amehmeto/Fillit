/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit_is_sample_valid.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amehmeto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/16 22:32:44 by amehmeto          #+#    #+#             */
/*   Updated: 2017/03/23 11:07:51 by amehmeto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Libft/libft.h"
#include "fillit.h"

#define BUFF_SIZE 21

/*
** *****************************************************************************
*/

static size_t		ft_strlen_mod(const char *s)
{
	int		i;

	i = 0;
	while (s[i] != '\n')
		i++;
	return (i);
}

static size_t		ft_sharp_counter(const char *s)
{
	int		i;
	int		c;

	i = 0;
	c = 0;
	while (s[i])
		if (s[i++] == '#')
			c++;
	return (c);
}

static int			ft_only_sharps_and_points(char *s)
{
	int		i;

	i = 0;
	while (s[i])
	{
		if (s[i] != '\n' && s[i] != '.' && s[i] != '#')
			return (1);
		i++;
	}
	return (0);
}

/*
** *****************************************************************************
*/

int				ft_error(char *str)
{
	write (2, str, ft_strlen(str));
	return (-1);
}

if (x < 8)
	return (ft_error("x inferieur a 8"));

int					fillit_is_sample_valid(char *path)
{
	int		fd;
	int		ret;
	char	buffer[BUFF_SIZE + 1];
	int		i;
	int		n;
	int		a;

	fd = open(path, O_RDWR);
	if (fd == -1)
		ft_putstr("open error\n");
/*
** while BUFF_LEN = 21
*/
	while ((ret = read(fd, buffer, BUFF_SIZE)) == 21)
	{
		buffer[ret] = '\0';
/*
** Only . or # in description
*/
		if ((a = ft_only_sharps_and_points(buffer)))
			return (10);
/*
** Not more than 4 sharps in description
*/
		if (ft_sharp_counter(buffer) != 4)
			return (20);
/*
** Check if stricly begins with description, seperated by one line.
*/
		i = 0;
		if (ret == 21)
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
/*
** Everything OK, then remodel and print it
*/
		fillit_tetri_remodel(buffer);
		ft_putstr(buffer);
	}
/*
** If BUFF_LEN = 20
*/
	if (ret == 20)
	{
		buffer[ret] = '\0';
/*
** Only . or # in description
*/
		if ((a = ft_only_sharps_and_points(buffer)))
			return (11);
/*
** Not more than 4 sharps in description
*/
		if (ft_sharp_counter(buffer) != 4)
			return (22);
/*
** Check if stricly ends with description only
*/
		i = 0;
		if (ft_strlen_mod(&buffer[i]) == 4)
		{
			n = 4;
			while (n--)
			{
				if (ft_strlen_mod(&buffer[i]) == 4)
					i += 5;
				else
					return (50 + n);
			}
		}
/*
** Everything OK, then remodel and  print it
*/
		fillit_tetri_remodel(buffer);
		ft_putstr(buffer);
	}
	else
		return (60);
	buffer[ret] = '\0';
	if (close(fd) == -1)
		ft_putstr("close error\n");
	return (0);
}
