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

	if (!check_codege(process->op_id, game->area[process->pc + 1].value))
	{
		game->area[process->pc].pc = 0;
		process->pc += jump_pc(game->area[process->pc + 1].value,
			process->op_id);
		process->op_id = 16;
		return ;
	}
	res = process->REG_NUM[game->area[process->pc + 2].value - 1] -
		process->REG_NUM[game->area[process->pc + 3].value - 1];
	process->REG_NUM[game->area[process->pc + 4].value - 1] = res;
	game->area[process->pc].pc = 0;
	process->pc += 5;
	if (res == 0)
		process->carry = 1;
	else
		process->carry = 0;
}
