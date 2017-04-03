/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amehmeto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/16 22:52:12 by amehmeto          #+#    #+#             */
/*   Updated: 2017/04/01 14:09:48 by amehmeto         ###   ########.fr       */
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
int	fillit_resolver(unsigned long long tetri[27][4]);
int		fillit_displayer(unsigned long long tetri[27][4], int size, int i);
void	grid_init(unsigned long long square[4], int size);
void	tetri_cpy(unsigned long long tetri[27][4], unsigned long long temp_tetri[27][4]);

#endif
