/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_players.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oshvorak <oshvorak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/29 10:53:13 by oshvorak          #+#    #+#             */
/*   Updated: 2018/06/13 14:14:36 by oshvorak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/corewar_vm.h"

void	add_player(t_game *game, char *file, int j)
{
	game->players[j] = read_player(file, game);
	game->players[j].id = j + 1;
	game->players[j].live = 1;
	game->players[j].count_lives = 0;
	game->players[j].color = j;
	game->players[j].last_live = 0;
	game->players[j].lives_in_cp = 0;
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
	init(game);
	j = 0;
	create_fla(&game->flags);
	while (i < ac)
	{
		i += flags_read(av + i, ac, &game->flags);
		if (i < ac)
		{
			if (j > 3)
				ft_error("Too many champions!", game);
			add_player(game, av[i], j);
			game->players_num++;
			i++;
			j++;
		}
	}
	fill_area(game);
	return (game);
}
