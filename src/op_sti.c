/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_sti.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oshvorak <oshvorak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/02 12:47:38 by oshvorak          #+#    #+#             */
/*   Updated: 2018/06/09 18:25:57 by oshvorak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/corewar_vm.h"

void	op_sti(t_game *game, t_process *process)
{
	unsigned int	arg2;
	unsigned int	arg3;
	int 			PC_jump;
	unsigned int    tmp;

	PC_jump = 3;
	if (!check_codege(process->op_id, game->area[process->PC + 1].value))
	{
		game->area[process->PC].PC = 0;
		process->PC += jump_pc(game->area[process->PC + 1].value, process->op_id);
		process->op_id = 16;
		return ;
	}
	if (ret_arg(game->area[process->PC + 1].value, MASK_2, 4) == T_DIR)
	{
		arg2 = write_2_bytes(game, process->PC + 3);
		arg2 = (short)arg2;
		PC_jump += 2;
	}
	else if (ret_arg(game->area[process->PC + 1].value, MASK_2, 4) == T_IND)
	{
		arg2 = write_4_bytes(game, game->area[process->PC + 3].value % IDX_MOD);
		PC_jump += 2;
	}
	else
	{
		arg2 = process->REG_NUM[game->area[process->PC + 3].value - 1];
		PC_jump += 1;
	}
	if (ret_arg(game->area[process->PC + 1].value, MASK_3, 2) == T_DIR)
	{
		arg3 = write_2_bytes(game, PC_jump + process->PC);
		arg3 = (short)arg3;
		PC_jump += 2;
	}
	else
	{
		arg3 = process->REG_NUM[game->area[process->PC + PC_jump].value - 1];
		PC_jump++;
	}
	tmp = (process->PC + (((int)arg2 + (int)arg3) % IDX_MOD)) % MEM_SIZE;
	game->area[tmp].value = 0;
	game->area[tmp + 1].value = 0;
	game->area[tmp + 2].value = 0;
	game->area[tmp + 3].value = 0;
	game->area[tmp].value |= process->REG_NUM[game->area[process->PC + 2].value - 1] >> 24;
	game->area[tmp + 1].value |= process->REG_NUM[game->area[process->PC + 2].value - 1] >> 16;
	game->area[tmp + 2].value |= process->REG_NUM[game->area[process->PC + 2].value - 1] >> 8;
	game->area[tmp + 3].value |= process->REG_NUM[game->area[process->PC + 2].value - 1];
	game->area[tmp].bold = 10;
	game->area[tmp + 1].bold = 10;
	game->area[tmp + 2].bold = 10;
	game->area[tmp + 3].bold = 10;
	game->area[tmp].color = process->color;
	game->area[tmp + 1].color = process->color;
	game->area[tmp + 2].color = process->color;
	game->area[tmp + 3].color = process->color;
	game->area[process->PC].PC = 0;
	process->PC += PC_jump;
}
