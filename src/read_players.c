/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_players.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aryabenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/29 10:53:13 by oshvorak          #+#    #+#             */
/*   Updated: 2018/06/12 15:41:25 by aryabenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/corewar_vm.h"

void	add_player(t_game *game, char *file, int j)
{
	game->players[j] = read_player(file);
	game->players[j].id = j + 1;
	game->players[j].live = 1;
	game->players[j].count_lives = 0;
	game->players[j].color = j;
	game->players[j].last_live = 0;
	game->players[j].lives_in_CP = 0;
	game->players[j].n = j > 0 && game->flags.n == -1 ? \
		game->players[j - 1].n - 1 : game->flags.n;
	game->flags.n = -1;
}

t_game	*read_players(char **av, int ac, int i)
{
	int		j;
	t_game	*game;

	if (!(game = (t_game*)malloc(sizeof(t_game))))
		return (0);
	game->process = NULL;
	game->CYCLE = 0;
	j = 0;
	create_fla(&game->flags);
	while (i < ac)
	{
		i += flags_read(av + i, ac, &game->flags);
		if (i < ac && j < 4)
		{
			add_player(game, av[i], j);
			i++;
			j++;
		}
	}
	fill_area(game);
	return (game);
}
