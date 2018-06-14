/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_lldi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oshvorak <oshvorak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/07 11:52:06 by oshvorak          #+#    #+#             */
/*   Updated: 2018/06/14 15:26:38 by oshvorak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/corewar_vm.h"

static unsigned int	ret_arg1(t_game *game, t_process *process, unsigned int codage)
{
	unsigned int	arg1;
	unsigned int	t_ind;
	
	if (ret_arg(codage, MASK_1, 6) == T_DIR)
	{
		arg1 = write_2_bytes(game, (process->pc + 2) % MEM_SIZE);
		arg1 = (short)arg1;
		process->pc = (process->pc + 4) % MEM_SIZE;
	}
	else if (ret_arg(game->area[(process->pc + 1) % MEM_SIZE].value, MASK_1, 6) == T_IND)
	{
		t_ind = (short)write_2_bytes(game, (process->pc + 2) % MEM_SIZE);
		arg1 = write_4_bytes(game, ((t_ind % IDX_MOD) + process->pc) % MEM_SIZE);
		process->pc = (process->pc + 4) % MEM_SIZE;
	}
	else
	{
		arg1 = process->reg_num[game->area[(process->pc + 2) % MEM_SIZE].value - 1];
		process->pc = (process->pc + 3) % MEM_SIZE;
	}
	return (arg1);
}

static unsigned int	ret_arg2(t_game *game, t_process *process, unsigned int codage)
{
	unsigned int	arg2;
	
	if (ret_arg(codage, MASK_2, 4) == T_DIR)
	{
		arg2 = write_2_bytes(game, process->pc);
		arg2 = (short)arg2;
		process->pc = (process->pc + 2) % MEM_SIZE;
	}
	else
	{
		arg2 = process->reg_num[game->area[process->pc].value - 1];
		process->pc = (process->pc + 1) % MEM_SIZE;
	}
	return (arg2);
}

void		op_lldi(t_game *game, t_process *process)
{
	unsigned int	arg1;
	unsigned int	arg2;
	unsigned int	arg3;
	unsigned int	codage;
	int				pc_buf;
	
	if (!check_codege(process->op_id, game->area[process->pc + 1].value))
	{
		game->area[process->pc].pc = 0;
		process->pc += jump_pc(game->area[(process->pc + 1) % MEM_SIZE].value, \
		process->op_id);
		process->pc %= MEM_SIZE;
		process->op_id = 16;
		return ;
	}
	pc_buf = process->pc;
	codage = game->area[(process->pc + 1) % MEM_SIZE].value;
	game->area[process->pc].pc = 0;
	arg1 = ret_arg1(game, process, codage);
	arg2 = ret_arg2(game, process, codage);
	arg3 = game->area[process->pc++].value;
	process->pc %= MEM_SIZE;
	process->reg_num[arg3 - 1] = write_4_bytes(game, (((int)arg1 \
	+ (int)arg2) + pc_buf) % MEM_SIZE);
	process->carry = (process->reg_num[arg3 - 1] == 0) ? 1 : 0;
}