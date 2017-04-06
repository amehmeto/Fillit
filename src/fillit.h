/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amehmeto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/16 22:52:12 by amehmeto          #+#    #+#             */
/*   Updated: 2017/04/06 22:10:05 by amehmeto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLIT_H
# define FILLIT_H

# include "../Libft/libft.h"
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdio.h>

int		fillit_is_sample_valid(int fd);
void	fillit_encoder(int fd, unsigned long long t[27][4]);
int		fillit_resolver(unsigned long long t[27][4]);
int		fillit_displayer(unsigned long long t[27][4], int size, int i);
int		square_vs_t(unsigned long long s[4], unsigned long long t[27][4],
																		int i);

#endif
