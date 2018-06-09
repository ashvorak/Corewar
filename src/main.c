/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oshvorak <oshvorak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/25 16:26:00 by oshvorak          #+#    #+#             */
/*   Updated: 2018/06/09 13:33:31 by oshvorak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/corewar_vm.h"

void	ft_error(void)
{
	ft_printf("Error\n");
	exit(1);
}

int		main(int ac, char **av)
{
	t_game	*game;

	//number = 2;
	//initscr();
	//noecho();
	//cbreak();
	//nodelay(stdscr, TRUE);
	//curs_set(FALSE);
	game = read_players(av, ac, 1);
	game->players_num = players_num(game) + 1;
	start_game(game);
	//nodelay(stdscr, FALSE);
	//manage_keys(game, getch());
	//endwin();
	return (0);
}
