/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_players.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aryabenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/29 10:53:13 by oshvorak          #+#    #+#             */
/*   Updated: 2018/06/12 14:12:10 by aryabenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/corewar_vm.h"

t_game	*read_players(char **av, int ac, int i)
{
	int		j;
	t_game	*game;

	if (!(game = (t_game*)malloc(sizeof(t_game))))
		return (0);
	game->process = NULL;
	game->CYCLE = 0;
	j = 0;
	while (i < ac && j < 4)
	{
		game->players[j] = read_player(av[i]);
		game->players[j].id = j + 1;
		game->players[j].live = 1;
		game->players[j].count_lives = 0;
		game->players[j].color = j;
		game->players[j].last_live = 0;
		game->players[j].lives_in_CP = 0;
		i++;
		j++;
	}
	fill_area(game);
	return (game);
}
