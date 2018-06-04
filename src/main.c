/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oshvorak <oshvorak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/25 16:26:00 by oshvorak          #+#    #+#             */
/*   Updated: 2018/06/01 14:40:32 by oshvorak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/corewar_vm.h"

void	ft_error(void)
{
	ft_printf("Error\n");
	exit(1);
}

int	main(int ac, char **av)
{
	t_game	*game;

	//initscr();
	//noecho();
	//curs_set(FALSE);
	game = read_players(av, ac, 1);
	start_game(game);
	//endwin();
	return (0);
}