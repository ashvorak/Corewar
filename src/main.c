/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aryabenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/25 16:26:00 by oshvorak          #+#    #+#             */
/*   Updated: 2018/06/12 15:29:45 by aryabenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include "../inc/corewar_vm.h"

void		ft_error(char *str)
{
	errno = 5;
	perror(str);
	exit(1);
}

static void	init(t_game *game)
{
	game->pause = 1;
	game->speed = 2000;
	game->checks = 0;
	game->cycle_to_die = CYCLE_TO_DIE;
}

int			main(int ac, char **av)
{
	t_game	*game;

	number = 2;
	game = read_players(av, ac, 1);
	game->players_num = players_num(game) + 1;
	init(game);
	if (game->flags.v)
	{
		initscr();
		noecho();
		cbreak();
		nodelay(stdscr, TRUE);
		curs_set(FALSE);
	}
	start_game(game);
	if (game->flags.v)
	{
		nodelay(stdscr, FALSE);
		manage_keys(game, getch());
		endwin();
	}
	return (0);
}
