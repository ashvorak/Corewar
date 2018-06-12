/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_and.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oshvorak <oshvorak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/12 15:43:04 by oshvorak          #+#    #+#             */
/*   Updated: 2018/06/12 16:00:41 by oshvorak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/corewar_vm.h"

unsigned int	write_arg(t_process *process, t_game *game, int tt, int pc)
{
	unsigned int tmp;

	if (tt == T_DIR)
		return (write_4_bytes(game, pc));
	else if (tt == T_IND)
	{
		tmp = write_2_bytes(game, pc);
		return (write_4_bytes(game, pc + (short)tmp));
	}
	else
	{
		tmp = game->area[pc].value;
		return (process->REG_NUM[(unsigned char)tmp - 1]);
	}
}

int				plus_pc(int codage, int mask, int move)
{
	if (ret_arg(codage, mask, move) == T_REG)
		return (1);
	else if (ret_arg(codage, mask, move) == T_DIR)
		return (4);
	else
		return (2);
}

void			op_and(t_game *game, t_process *process)
{
	int				pc_buf;
	unsigned int	arg1;
	unsigned int	arg2;
	unsigned int	arg3;

	if (!check_codege(process->op_id, game->area[process->PC + 1].value))
	{
		game->area[process->PC].PC = 0;
		process->PC += jump_pc(game->area[process->PC + 1].value, \
		process->op_id);
		process->op_id = 16;
		return ;
	}
	pc_buf = 2;
	arg1 = write_arg(process, game, \
	ret_arg(game->area[process->PC + 1].value, MASK_1, 6), \
	process->PC + pc_buf);
	pc_buf += plus_pc(game->area[process->PC + 1].value, MASK_1, 6);
	arg2 = write_arg(process, game, \
	ret_arg(game->area[process->PC + 1].value, MASK_2, 4), \
	process->PC + pc_buf);
	pc_buf += plus_pc(game->area[process->PC + 1].value, MASK_2, 4);
	arg3 = game->area[process->PC + pc_buf].value;
	pc_buf += 1;
	process->REG_NUM[arg3 - 1] = arg1 & arg2;
	process->carry = (process->REG_NUM[arg3 - 1] == 0) ? 1 : 0;
	game->area[process->PC].PC = 0;
	process->PC += pc_buf;
}
