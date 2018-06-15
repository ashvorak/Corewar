/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_add.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oshvorak <oshvorak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/12 15:22:35 by oshvorak          #+#    #+#             */
/*   Updated: 2018/06/13 19:45:43 by oshvorak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/corewar_vm.h"

int     checking_regs(t_game *game, t_process *process, int i)
{
	if (!check_reg_ind(game, process, game->area[(process->pc + i) % MEM_SIZE].value))
		return (0);
	if (!check_reg_ind(game, process, game->area[(process->pc + i + 1) % MEM_SIZE].value))
		return (0);
	if (!check_reg_ind(game, process, game->area[(process->pc + i + 2) % MEM_SIZE].value))
		return (0);
	return (1);
}

void	op_add(t_game *game, t_process *process)
{
	if (!check_codege(process->op_id, game->area[(process->pc + 1) % MEM_SIZE].value))
	{
		game->area[process->pc].pc = 0;
		process->pc += jump_pc(game->area[(process->pc + 1) % MEM_SIZE].value, \
		process->op_id);
		process->pc %= MEM_SIZE;
		process->op_id = 16;
		return ;
	}
	if (checking_regs(game, process, 2))
	{
		process->reg_num[game->area[(process->pc + 4) % MEM_SIZE].value - 1] =
				process->reg_num[game->area[(process->pc
				                             + 2) % MEM_SIZE].value - 1] + process->reg_num[game->area[(process->pc +
				                                                                                        3) % MEM_SIZE].value - 1];
		if (process->reg_num[game->area[(process->pc + 4) % MEM_SIZE].value - 1] == 0)
			process->carry = 1;
		else
			process->carry = 0;
	}
	game->area[process->pc].pc = 0;
	process->pc = (process->pc + 5);
}
