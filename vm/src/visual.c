/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visual.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oshvorak <oshvorak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/24 15:55:28 by dlytvyn           #+#    #+#             */
/*   Updated: 2018/06/12 12:39:38 by oshvorak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/corewar_vm.h"

int		get_first_reg(int n, t_game *game, int pos)
{
	if (n != -1)
		return (n);
	else
	{
		if (pos - 1 >= 0)
			return (game->players[pos - 1].n - 1);
		else
			return (n);
	}
}

void	visual(t_game *game)
{
	initialize_colors();
	print_frame(stdscr, game->speed);
	print_data(game);
	right_menu(game);
	refresh();
}
