/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_game.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oshvorak <oshvorak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/01 13:16:10 by oshvorak          #+#    #+#             */
/*   Updated: 2018/06/02 14:20:47 by oshvorak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/corewar_vm.h"

static void	execute_process(t_game *game)
{

}

static int	push_op_id(char *value)
{
	int i;

	i = 0;
	while (i < 16)
	{
		if (!ft_strcmp(value, op_tab[i].hex))
			return (op_tab[i].id);
		i++;
	}
	return (0);
}

static void	execute_processes(t_game *game)
{
	t_process *process;

	process = game->process;
	while (process)
	{
		if (process->op_id)
		{
			if (process->CYCLE_TO_DONE == op_tab[process->op_id].CYCLES)
			{
				//execute_process(game);
				process->CYCLE_TO_DONE = 0;
			}
			else
				process->CYCLE_TO_DONE++;
		}
		else
		{
			process->location += process->location + 1 == MEM_SIZE ? -process->location : 1;
			process->op_id = push_op_id(game->area[process->location].value);
		}
		process = process->next;
	}
}

void	start_game(t_game *game)
{
	while (game->process)
	{
		execute_proccess(game);
		game->CYCLE++;
	}
}
