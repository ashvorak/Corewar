/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_add.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oshvorak <oshvorak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/12 15:22:35 by oshvorak          #+#    #+#             */
/*   Updated: 2018/06/12 15:26:44 by oshvorak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/corewar_vm.h"

void	op_add(t_game *game, t_process *process)
{
	if (!check_codege(process->op_id, game->area[process->PC + 1].value))
	{
		game->area[process->PC].PC = 0;
		process->PC += jump_pc(game->area[process->PC + 1].value, \
		process->op_id);
		process->op_id = 16;
		return ;
	}
	game->process->REG_NUM[game->area[process->PC + 4].value - 1] =
		process->REG_NUM[game->area[process->PC
		+ 2].value - 1] + process->REG_NUM[game->area[process->PC +
		3].value - 1];
	game->area[process->PC].PC = 0;
	process->PC += 5;
	if (game->process->REG_NUM[game->area[process->PC + 4].value - 1] == 0)
		process->carry = 1;
	else
		process->carry = 0;
}
