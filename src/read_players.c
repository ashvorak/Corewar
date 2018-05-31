/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_players.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oshvorak <oshvorak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/29 10:53:13 by oshvorak          #+#    #+#             */
/*   Updated: 2018/05/31 18:41:01 by oshvorak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/corewar_vm.h"

void		read_players(t_game *game, char **av, int ac, int i)
{
	int j;

	j = 0;
	while (i < ac && j < 4)
	{
		game->players[j].color = j;
		game->players[j] = read_player(av[i]);
		i++;
		j++;
	}
}
