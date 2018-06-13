/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_sub.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oshvorak <oshvorak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/12 16:00:29 by dlytvyn           #+#    #+#             */
/*   Updated: 2018/06/13 14:42:33 by oshvorak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/corewar_vm.h"

void	op_sub(t_game *game, t_process *process)
{
	unsigned int res;

	if (!check_codege(process->op_id, game->area[(process->pc + 1) % MEM_SIZE].value))
	{
		game->area[(process->pc) % MEM_SIZE].pc = 0;
		process->pc += jump_pc(game->area[(process->pc + 1) % MEM_SIZE].value,
			process->op_id);
		process->op_id = 16;
		return ;
	}
	res = process->reg_num[game->area[(process->pc + 2) % MEM_SIZE].value - 1] -
		process->reg_num[game->area[(process->pc + 3) % MEM_SIZE].value - 1];
	process->reg_num[game->area[(process->pc + 4) % MEM_SIZE].value - 1] = res;
	game->area[process->pc].pc = 0;
	process->pc += 5;
	process->pc %= MEM_SIZE;
	process->carry = (res == 0) ? 1 : 0;	
}
