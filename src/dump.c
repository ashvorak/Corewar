/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dump.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oshvorak <oshvorak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/13 09:29:19 by dlytvyn           #+#    #+#             */
/*   Updated: 2018/06/15 17:33:02 by oshvorak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/corewar_vm.h"

void	dump_memory(t_game *game)
{
	unsigned int i;

	i = 0;
	while (i < MEM_SIZE)
	{
		if (i % 64 == 0)
			ft_printf("\n0x%.4x : ", i);
		ft_printf("%.2x ", game->area[i].value);
		i++;
	}
	printf("\n");
	finish_game(game);
}
