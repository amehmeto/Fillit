/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit_is_sample_valid.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amehmeto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/16 22:32:44 by amehmeto          #+#    #+#             */
/*   Updated: 2017/01/19 08:12:31 by amehmeto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Libft/libft.h"
#include "fillit.h"

# define BUFF_SIZE 21

static size_t		ft_strlen_mod(const char *s)
{
	int		i;

	i = 0;
	while (s[i] != '\n')
	{
		i++;
	}
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

int		fillit_is_sample_valid(char *path)
{
	int		fd;
	int		ret;
	char	buffer[BUFF_SIZE + 1];
	int		status; /* Status ? sample OK : sample KO; */
	int		i = 0;
	int		n;
	int		a;
 
	status = 1;
	fd = open(path, O_RDWR);
	if (fd == -1)
		ft_putstr("open error\n");
	while ((ret = read(fd, buffer, BUFF_SIZE)))
	{
		buffer[ret] = '\0';
		/* Only . or # in description */
		while (buffer[i])
		{
			if (buffer[i] != '\n' && buffer[i] != '.' && buffer[i] != '#')
				return (11);
			i++;
		}
		/* Not more than 4 sharps in description */
		if (ft_sharp_counter(buffer) > 4)
			return (22);
		/* Check if begin with one description; 
		** seperated by one line,
		** stricly end with description only*/
		i = 0;
		while (buffer[i])
		{
			n = 3;
			while (n--)
			{
				if (ft_strlen_mod(&buffer[i]) == 4)
					i += 4;
				else
					return (30 + n);
			}
			if (ft_strlen_mod(&buffer[i]) == 4)
				i ++;
			else
				return (30 + n);
			if ((a = ft_strlen_mod(&buffer[i])) == 0)
				i++;
			else
				return (a);
		}
		/* Everything OK, then print it */
		ft_putstr(buffer);
	}
	buffer[ret] = '\0';
	if (close(fd) == -1)
		ft_putstr("close error\n");
	return (0);
}
