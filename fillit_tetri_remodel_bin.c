/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit_tetri_remodel_bin.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amehmeto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/23 14:51:46 by amehmeto          #+#    #+#             */
/*   Updated: 2017/03/25 21:48:16 by amehmeto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Libft/libft.h"
#include "fillit.h"

void			fillit_tetri_remodel(long long tetri)
{
	while (tetri < 0b0000100000000000)
		tetri = tetri << 4;
	while (!(tetri & 0b1000100010001000))
		tetri = tetri << 1;
}
