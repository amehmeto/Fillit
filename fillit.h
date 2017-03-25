/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amehmeto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/16 22:52:12 by amehmeto          #+#    #+#             */
/*   Updated: 2017/03/25 21:36:37 by amehmeto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLIT_H
# define FILLIT_H

#include "Libft/libft.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>

struct mask	
{
	unsigned long long	first_quartr;
	unsigned long long	secnd_quartr;
	unsigned long long	third_quartr;
	unsigned long long	forth_quartr;
};

int				fillit_is_sample_valid(int fd);
void			fillit_tetri_remodel(char *s);
void			fillit_encoder(int fd, struct mask *tetri);

#endif
