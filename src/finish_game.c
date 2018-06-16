/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   finish_game.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oshvorak <oshvorak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/13 10:39:58 by dlytvyn           #+#    #+#             */
/*   Updated: 2018/06/15 21:03:29 by oshvorak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/corewar_vm.h"

void    show_players(t_game *game)
{
    int i;

    i = 0;
    while (game->players[i].magic && i < 4)
    {
        ft_printf("* Player %d, weighing %d bytes, \"%s\" !\n", i + 1,
            game->players[i].prog_size, game->players[i].prog_name);
        i++;
    }
}

void    finish_game(t_game *game)
{
    int tmp;
    int i;

    i = 1;
    tmp = game->players[0].last_live;
    if (!game->process || game->cycle_to_die <= 0)
    {
        game->finish = 1;
        while (i < game->players_num)
        {
            if (game->players[i].last_live > tmp)
                game->winner = i;
            i++;
        }
        if (game->flags.v)
            visual(game);
        else
            ft_printf("Player %d, \"%s\", has won!\n", game->winner + 1,
                game->players[game->winner].prog_name);
    }
}