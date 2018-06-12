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
	if (ret_arg(game->area[process->PC + 1].value, MASK_1, 6) == T_DIR)
	{
		*t_reg = game->area[process->PC + 6].value;
		process->REG_NUM[(unsigned char)*t_reg - 1] = write_4_bytes(game,
			process->PC + 2);
		game->area[process->PC].PC = 0;
		process->PC += 7;
	}
	else
	{
		*t_reg = game->area[process->PC + 4].value;
		*t_ind = write_2_bytes(game, process->PC + 2);
		process->REG_NUM[*t_reg - 1] = write_4_bytes(game,
			process->PC + (short)*t_ind);
		game->area[process->PC].PC = 0;
		process->PC += 5;
	}
}

void		op_lld(t_game *game, t_process *process)
{
	unsigned int	t_reg;
	unsigned int	t_ind;

	if (!check_codege(process->op_id, game->area[process->PC + 1].value))
	{
		game->area[process->PC].PC = 0;
		process->PC += jump_pc(game->area[process->PC + 1].value,
			process->op_id);
		process->op_id = 16;
		return ;
	}
	first_if(game, process, &t_reg, &t_ind);
	process->carry =
		game->process->REG_NUM[(unsigned char)t_reg - 1] == 0 ? 1 : 0;
}
