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

void	op_add(t_game *game, t_process *process)
{
	if (!check_codege(process->op_id, game->area[process->pc + 1].value))
	{
		game->area[process->pc].pc = 0;
		process->pc += jump_pc(game->area[process->pc + 1].value, \
		process->op_id);
		process->op_id = 16;
		return ;
	}
	process->reg_num[game->area[process->pc + 4].value - 1] =
		process->reg_num[game->area[process->pc
		+ 2].value - 1] + process->reg_num[game->area[process->pc +
		3].value - 1];
	game->area[process->pc].pc = 0;
	process->pc += 5;
	if (process->reg_num[game->area[process->pc + 4].value - 1] == 0)
		process->carry = 1;
	else
		process->carry = 0;
}
