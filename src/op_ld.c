/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_ld.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oshvorak <oshvorak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/07 11:52:06 by oshvorak          #+#    #+#             */
/*   Updated: 2018/06/11 15:03:18 by oshvorak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/corewar_vm.h"

void    op_ld(t_game *game, t_process *process)
{
	unsigned int    t_reg;
	unsigned int    t_ind;
	
	if (!check_codege(process->op_id, game->area[process->PC + 1].value))
	{
		game->area[process->PC].PC = 0;
		process->PC += jump_pc(game->area[process->PC + 1].value, process->op_id);
		process->op_id = 16;
		return ;
	}
	if (ret_arg(game->area[process->PC + 1].value, MASK_1, 6) == T_DIR)
	{
		t_reg = game->area[process->PC + 6].value;
		process->REG_NUM[(unsigned char)t_reg - 1] = write_4_bytes(game, process->PC + 2);
		game->area[process->PC].PC = 0;
		process->PC += 7;
	}
	else
	{
		t_reg = game->area[process->PC + 4].value;
		t_ind = write_2_bytes(game, process->PC + 2) % IDX_MOD;
		game->area[process->PC + 2].value |= (short)t_ind >> 8;
		game->area[process->PC + 2].value |= (short)t_ind;
		process->REG_NUM[t_reg - 1] = write_4_bytes(game, process->PC + (short)t_ind);
		game->area[process->PC].PC = 0;
		process->PC += 5;
	}
	process->carry = process->REG_NUM[t_reg - 1] == 0 ? 1 : 0;
}
