/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_lld.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oshvorak <oshvorak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/07 11:52:06 by oshvorak          #+#    #+#             */
/*   Updated: 2018/06/09 18:25:37 by oshvorak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/corewar_vm.h"

static void	first_if(t_game *game, t_process *process, unsigned int *t_reg,
	unsigned int *t_ind)
{
	if (ret_arg(game->area[process->pc + 1].value, MASK_1, 6) == T_DIR)
	{
		*t_reg = game->area[process->pc + 6].value;
		process->reg_num[(unsigned char)*t_reg - 1] = write_4_bytes(game,
			process->pc + 2);
		game->area[process->pc].pc = 0;
		process->pc += 7;
	}
	else
	{
		*t_reg = game->area[process->pc + 4].value;
		*t_ind = write_2_bytes(game, process->pc + 2);
		process->reg_num[*t_reg - 1] = write_4_bytes(game,
			process->pc + (short)*t_ind);
		game->area[process->pc].pc = 0;
		process->pc += 5;
	}
}

void		op_lld(t_game *game, t_process *process)
{
	unsigned int	t_reg;
	unsigned int	t_ind;

	if (!check_codege(process->op_id, game->area[process->pc + 1].value))
	{
		game->area[process->pc].pc = 0;
		process->pc += jump_pc(game->area[process->pc + 1].value,
			process->op_id);
		process->op_id = 16;
		return ;
	}
	first_if(game, process, &t_reg, &t_ind);
	process->carry =
		game->process->reg_num[(unsigned char)t_reg - 1] == 0 ? 1 : 0;
}
