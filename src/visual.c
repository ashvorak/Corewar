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

void			visual(t_game *game)
{
	initialize_colors();
	print_frame(stdscr, game->speed);
	print_data(game);
	right_menu(game);
	refresh();
}
