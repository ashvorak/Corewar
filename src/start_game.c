/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_game.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oshvorak <oshvorak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/01 13:16:10 by oshvorak          #+#    #+#             */
/*   Updated: 2018/06/01 15:24:12 by oshvorak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/corewar_vm.h"

static void	execute_process(t_game *game)
{

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
				execute_process(game);
			else
				process->CYCLE_TO_DONE++;
		}
		else
			process->location += process->location + 1 == MEM_SIZE ? 1 : -process->location;    // should be in reverse order
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
