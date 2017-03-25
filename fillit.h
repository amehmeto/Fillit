/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amehmeto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/16 22:52:12 by amehmeto          #+#    #+#             */
/*   Updated: 2017/03/24 19:04:49 by amehmeto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLIT_H
# define FILLIT_H

#include "Libft/libft.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>

int				fillit_is_sample_valid(int fd);
void			fillit_tetri_remodel(char *s);
struct tetri	*fillit_encoder(int fd, struct tetri *tetri);

struct	tetri
{
	unsigned long long	first_quartr;
	unsigned long long	secnd_quartr;
	unsigned long long	third_quartr;
	unsigned long long	forth_quartr;
};

#endif
