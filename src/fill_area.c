/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_area.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oshvorak <oshvorak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/31 18:37:49 by oshvorak          #+#    #+#             */
/*   Updated: 2018/05/31 18:56:37 by oshvorak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/corewar_vm.h"

static int	players_num(t_game *game)
{
	int i;

	i = 0;
	while (game->players[i].prog_size)
		i++;
	return (i - 1);
}

static void fill_players(t_game *game)
{
	int		i;
	int		j;
	int		n;
	int		pn;

	i = 0;
	j = 0;
	n = 0;
	pn = players_num(game);
	while (i < MEM_SIZE)
	{
		j = 0;
		if (n <= pn)
		{
			i = (0 + (MEM_SIZE / (pn + 1))) * n;
			while (j < (int)game->players[n].prog_size)
			{
				game->area[i].value = game->players[n].opcode[j];
				game->area[i].color = n;
				i++;
				j++;
			}
			n++;
		}
		i++;
	}
}

void	fill_area(t_game *game)
{
	int		i;

	i = 0;
	fill_players(game);
	while (i < MEM_SIZE)
	{
		if (!game->area[i].value)
		{
			game->area[i].value = ft_strdup("00");
			game->area[i].color = 10;
		}
		i++;
	}
}
