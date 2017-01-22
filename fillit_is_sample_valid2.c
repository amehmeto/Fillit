/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit_is_sample_valid2.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amehmeto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/22 03:52:16 by amehmeto          #+#    #+#             */
/*   Updated: 2017/01/22 06:45:55 by amehmeto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Libft/libft.h"
#include "fillit.h"


char		*tetri_array(int i)
{
	char	tetri[19][20];

	tetri[0] = "####\n....\n....\n....\n\0";
	tetri[1] = "#...\n#...\n#...\n#...\n\0";
	tetri[2] = ".##.\n##..\n....\n....\n\0";
	tetri[3] = "#...\n##..\n.#..\n....\n\0";
	tetri[4] = "##..\n.##.\n....\n....\n\0";
	tetri[5] = ".#..\n##..\n#...\n....\n\0";
	tetri[6] = "##..\n##..\n....\n....\n\0";
	tetri[7] = "##..\n#...\n#...\n....\n\0";
	tetri[8] = "###.\n..#.\n....\n....\n\0";
	tetri[9] = ".#..\n.#..\n##..\n....\n\0";
	tetri[10] = "#...\n###.\n....\n....\n\0";
	tetri[11] = "##..\n.#..\n.#..\n....\n\0";
	tetri[12] = "..#.\n###.\n....\n....\n\0";
	tetri[13] = "#...\n#...\n##..\n....\n\0";
	tetri[14] = "###.\n#...\n....\n....\n\0";
	tetri[15] = "###.\n.#..\n....\n....\n\0";
	tetri[16] = ".#..\n##..\n.#..\n....\n\0";
	tetri[17] = ".#..\n###.\n....\n....\n\0";
	tetri[18] = "#...\n##..\n#...\n....\n\0";
	tetri[19] = '\0';
	return (tetri[i]);
}


int		fillit_is_sample_valid2(char *s)
{
	int		i;
	int		a;

	i = 0;
	a = 70;
	while ((a = ft_strncmp(s, TETRI(i), 20)))
		i++;
	return (a);
}
