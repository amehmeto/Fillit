/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amehmeto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/16 22:52:12 by amehmeto          #+#    #+#             */
/*   Updated: 2017/03/31 13:26:49 by amehmeto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLIT_H
# define FILLIT_H

# include "Libft/libft.h"
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdio.h>

struct	mask
{
	unsigned long long	a;
	unsigned long long	b;
	unsigned long long	c;
	unsigned long long	d;
};

int		fillit_is_sample_valid(int fd);
void	fillit_encoder(int fd, unsigned long long tetri[27][4]);
void	fillit_resolver(unsigned long long tetri[27][4]);
int		fillit_displayer(unsigned long long tetri[27][4], int size, int i);
void	grid_init(unsigned long long square[4], int size);


#endif
