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

	if (!check_codege(process->op_id, game->area[process->PC + 1].value))
	{
		game->area[process->PC].PC = 0;
		process->PC += jump_pc(game->area[process->PC + 1].value,
			process->op_id);
		process->op_id = 16;
		return ;
	}
	res = process->REG_NUM[game->area[process->PC + 2].value - 1] -
		process->REG_NUM[game->area[process->PC + 3].value - 1];
	process->REG_NUM[game->area[process->PC + 4].value - 1] = res;
	game->area[process->PC].PC = 0;
	process->PC += 5;
	if (res == 0)
		process->carry = 1;
	else
		process->carry = 0;
}
