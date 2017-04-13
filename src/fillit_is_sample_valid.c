/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit_is_sample_valid.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amehmeto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/16 22:32:44 by amehmeto          #+#    #+#             */
/*   Updated: 2017/04/13 23:36:25 by amehmeto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

#define BUFF_SIZE 21

/*
** ************************************************************************** **
*/

int				fillit_is_sample_valid(int fd)
{
	char		buffer[BUFF_SIZE + 1];
	ssize_t		ret;
	int			a;

	while ((ret = read(fd, buffer, BUFF_SIZE)) == 21)
		if ((a = fillit_checker(buffer, ret)))
			return (a);
	if (ret == 0)
		return (1);
	if (ret == 20)
		if ((a = fillit_checker(buffer, ret)))
			return (a);
	buffer[ret] = '\0';
	if (ret != 20 && ret != 21 && ret != 0)
		return (1);
	if (close(fd) == -1)
		ft_putstr("close error\n");
	return (0);
}
