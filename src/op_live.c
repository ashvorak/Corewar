/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_live.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oshvorak <oshvorak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/12 16:15:52 by oshvorak          #+#    #+#             */
/*   Updated: 2018/06/14 15:29:08 by oshvorak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/corewar_vm.h"

int     get_player_num(t_game *game, int arg)
{
	int i;
	
	i = 0;
	while (i < game->players_num)
	{
		if (game->players[i].n == arg)
			return (i + 1);
		i++;
	}
	return (0);
}

char    *get_name(t_game *game, int arg)
{
	int i;
	
	i = 0;
	while (i < game->players_num)
	{
		if (game->players[i].n == arg)
			return (game->players[i].prog_name);
		i++;
	}
	return (0);
}

void	op_live(t_game *game, t_process *process)
{
	unsigned int	arg;
	int             num;
	
	num = 0;
	process->live++;
	arg = write_4_bytes(game, process->pc + 1);
	if (get_player_num(game, arg) > 0)
	{
		num = get_player_num(game, arg);
		//if (!game->flags.v)
		//	ft_printf("A process shows that player %d ( %s ) is alive\n", num, get_name(game, arg));
		game->players[num - 1].live = 1;
		game->players[num - 1].last_live = (int)game->cycle;
		game->players[num - 1].lives_in_cp++;
	}
	game->area[process->pc].pc = 0;
	process->pc = (process->pc + 5) % MEM_SIZE;
}
