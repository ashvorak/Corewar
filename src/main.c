/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oshvorak <oshvorak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/25 16:26:00 by oshvorak          #+#    #+#             */
/*   Updated: 2018/06/13 14:10:56 by oshvorak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include "../inc/corewar_vm.h"

void	ft_error(char *str, t_game *game)
{
	errno = 5;
	perror(str);
	free(game);
	game = NULL;
	exit(1);
}

void    exit_game(t_game *game)
{
	free(game);
	game = NULL;
	exit(0);
}

void	ft_usage(void)
{
	ft_printf("Usage: ./corewar [-dump N -n N -v <champion1.cor> <...>\n");
	ft_printf("       -dump N   : Dumps memory after N cycles then exits\n");
	ft_printf("       -n N      : sets the number of the next player\n");
	ft_printf("       -c        : Show cycles\n");
	ft_printf("       -v        : Ncurses output mode\n");
	exit(1);
}

void    init(t_game *game)
{
	game->pause = 1;
	game->speed = 2000;
	game->checks = 0;
	game->cycle_to_die = CYCLE_TO_DIE;
	game->num_proc = 0;
	game->players_num = 0;
	game->cycle = 0;
	game->n = 0;
	game->winner = 0;
	game->finish = 0;
	game->er = 0;
	ft_bzero(&game->area, sizeof(game->area));
	ft_bzero(&game->players, sizeof(game->players));
	game->process = NULL;
}

int		main(int ac, char **av)
{
	t_game	*game;

	g_number = 2;
	(ac < 2) ? ft_usage() : 0;
	game = read_players(av, ac, 1);
	game->players_num = players_num(game) + 1;
	
	game->fd = open("traces.txt", O_WRONLY);
	
	if (game->flags.v)
	{
		initscr();
		noecho();
		cbreak();
		nodelay(stdscr, TRUE);
		curs_set(FALSE);
	}
	if (!game->flags.v)
		show_players(game);
	start_game(game);
	if (game->flags.v)
	{
		nodelay(stdscr, FALSE);
		manage_keys(game, getch());
		nocbreak();
		endwin();
	}
	exit_game(game);
	return (0);
}
