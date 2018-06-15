/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_sub.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlytvyn <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/12 16:00:29 by dlytvyn           #+#    #+#             */
/*   Updated: 2018/06/12 16:00:30 by dlytvyn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/corewar_vm.h"

void	op_sub(t_game *game, t_process *process)
{
	unsigned int res;

	res = 0;
	if (!check_codege(process->op_id, game->area[(process->pc + 1) % MEM_SIZE].value))
	{
		game->area[process->pc].pc = 0;
		process->pc += jump_pc(game->area[(process->pc + 1) % MEM_SIZE].value,
			process->op_id);
		process->pc %= MEM_SIZE;
		process->op_id = 16;
		return ;
	}
	if (checking_regs(game, process, 2))
	{
		res = process->reg_num[game->area[(process->pc + 2) % MEM_SIZE].value - 1] -
		      process->reg_num[game->area[(process->pc + 3) % MEM_SIZE].value - 1];
		process->reg_num[game->area[(process->pc + 4) % MEM_SIZE].value - 1] = res;
		if (res == 0)
			process->carry = 1;
		else
			process->carry = 0;
		
	}
	game->area[process->pc].pc = 0;
	process->pc = (process->pc + 5) % MEM_SIZE;
}
