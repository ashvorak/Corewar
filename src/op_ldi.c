/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_ldi.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oshvorak <oshvorak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/07 11:52:06 by oshvorak          #+#    #+#             */
/*   Updated: 2018/06/12 16:35:17 by oshvorak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/corewar_vm.h"

static int	ret_arg1(t_game *game, t_process *process, unsigned int codage)
{
	unsigned int	arg1;
	unsigned int	t_ind;

	if (ret_arg(codage, MASK_1, 6) == T_DIR)
	{
		arg1 = write_2_bytes(game, process->PC + 2);
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
	return (arg1);
}

static int	ret_arg2(t_game *game, t_process *process, unsigned int codage)
{
	unsigned int	arg2;

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
	return (arg2);
}

void		op_ldi(t_game *game, t_process *process)
{
	unsigned int	arg1;
	unsigned int	arg2;
	unsigned int	arg3;
	unsigned int	codage;
	int				pc_buf;

	if (!check_codege(process->op_id, game->area[process->PC + 1].value))
	{
		game->area[process->PC].PC = 0;
		process->PC += jump_pc(game->area[process->PC + 1].value, \
		process->op_id);
		process->op_id = 16;
		return ;
	}
	pc_buf = process->PC;
	codage = game->area[process->PC + 1].value;
	game->area[process->PC].PC = 0;
	arg1 = ret_arg1(game, process, codage);
	arg2 = ret_arg2(game, process, codage);
	arg3 = game->area[process->PC++].value;
	process->REG_NUM[arg3 - 1] = write_4_bytes(game, (((int)arg1 \
	+ (int)arg2) % IDX_MOD) + pc_buf);
}
