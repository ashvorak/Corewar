/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_lldi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oshvorak <oshvorak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/07 11:52:06 by oshvorak          #+#    #+#             */
/*   Updated: 2018/06/08 13:40:15 by oshvorak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/corewar_vm.h"

void    op_lldi(t_game *game, t_process *process)
{
	unsigned int 	arg1;
	unsigned int 	arg2;
	unsigned int 	arg3;
	unsigned int 	codage;
	int 	        t_ind;
	int 			PC_buf;

	if (!check_codege(process->op_id, game->area[process->PC + 1].value))
	{
		game->area[process->PC].PC = 0;
		process->PC += 2;
		process->op_id = 16;
		return;
	}
	PC_buf = process->PC;
	codage = game->area[process->PC + 1].value;
	game->area[process->PC].PC = 0;
	if (ret_arg(codage, MASK_1, 6) == T_DIR)
	{
		arg1 = write_2_bytes(game, process->PC + 2);
	//	game->area[process->PC].PC = 0;
		arg1 = (short)arg1;
		process->PC += 4;
	}
	else if (ret_arg(game->area[process->PC + 1].value, MASK_1, 6) == T_IND)
	{
		t_ind = write_2_bytes(game, process->PC + 2);
		arg1 = write_4_bytes(game, ((short)t_ind % IDX_MOD) + process->PC);
		process->PC += 4;
	}
	else
	{
		arg1 = process->REG_NUM[game->area[process->PC + 2].value - 1];
		process->PC += 3;
	}
	if (ret_arg(codage, MASK_2, 4) == T_DIR)
	{
		arg2 = write_2_bytes(game, process->PC);
		arg2 = (short)arg2;
		process->PC += 2;
	}
	else
	{
		arg2 = process->REG_NUM[game->area[process->PC].value - 1];
		process->PC += 1;
	}
	arg3 = game->area[process->PC++].value;
	process->REG_NUM[arg3 - 1] = write_4_bytes(game, ((arg1 + arg2)) + PC_buf);
}