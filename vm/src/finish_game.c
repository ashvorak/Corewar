/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   finish_game.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlytvyn <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/13 10:39:58 by dlytvyn           #+#    #+#             */
/*   Updated: 2018/06/13 10:39:59 by dlytvyn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/corewar_vm.h"

void	delete_process(t_game *game)
{
	t_process *tmp;
	t_process *buf;

	tmp = game->process;
	while (tmp)
	{
		buf = tmp->next;
		free(tmp);
		tmp = buf;
	}
	game->process = NULL;
}

void	show_players(t_game *game)
{
	int i;

	i = 0;
	while (game->players[i].magic && i < 4)
	{
		ft_printf("* Player %d, weighing %d bytes, \"%s\", ( \"%s\" ) !\n",
			i + 1, game->players[i].prog_size,
			game->players[i].prog_name, game->players[i].comment);
		i++;
	}
}

void	finish_game(t_game *game)
{
	int tmp;
	int i;

	i = game->players_num - 2;
	tmp = game->players[game->players_num - 1].last_live;
	game->winner = game->players_num - 1;
	if (!game->process || game->cycle_to_die <= 0)
	{
		game->finish = 1;
		while (i >= 0)
		{
			if (game->players[i].last_live > tmp)
			{
				game->winner = i;
				tmp = game->players[i].last_live;
			}
			i--;
		}
		if (game->flags.v)
			visual(game);
		else
			ft_printf("Player %d, \"%s\", has won!\n", game->winner + 1,
				game->players[game->winner].prog_name);
	}
}
