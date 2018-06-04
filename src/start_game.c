/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_game.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oshvorak <oshvorak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/01 13:16:10 by oshvorak          #+#    #+#             */
/*   Updated: 2018/06/04 11:23:53 by oshvorak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/corewar_vm.h"

static void	execute_process(t_game *game, t_process *process)
{
	//if (process->op_id == 0)
	//	op_live(game, process);
	//else if (process->op_id == 3)
	//	op_add(game, process);
	//else if (process->op_id == 4)
	//	op_sub(game, process);
	if (process->op_id == 7)
		op_and(game, process);
	else if (process->op_id == 8)
		op_zjmp(game, process);
	else if (process->op_id == 10)
		op_sti(game, process);
	else if (process->op_id == 15)
		op_aff(game, process);
}

static int	push_op_id(unsigned char value)
{
	int i;

	i = 0;
	while (i < 16)
	{
		if (value == op_tab[i].id + 1)
			return (op_tab[i].id);
		i++;
	}
	return (16);
}

static void	execute(t_game *game)
{
	t_process *process;

	process = game->process;
	while (process)
	{
		if (process->op_id != 16)
		{
			if (process->CYCLE_TO_DONE == op_tab[process->op_id].CYCLES)
			{
				execute_process(game, process);
				process->op_id = 16;
				process->PC += process->PC + 1 == MEM_SIZE ? -process->PC : 1;
				process->CYCLE_TO_DONE = 0;
			}
			else
				process->CYCLE_TO_DONE++;
		}
		else
		{
			process->PC += process->PC + 1 == MEM_SIZE ? -process->PC : 1;
			process->op_id = push_op_id(game->area[process->PC].value);
		}
		process = process->next;
	}
}

void	start_game(t_game *game)
{
	t_process *process;

	process = game->process;
	while (process)
	{
		process->op_id = push_op_id(game->area[process->PC].value);
		process = process->next;
	}
	while (game->process && game->CYCLE < 50)
	{
		execute(game);
		game->CYCLE++;
		visual(game);
	}
}
