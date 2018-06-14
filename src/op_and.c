/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_and.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oshvorak <oshvorak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/12 15:43:04 by oshvorak          #+#    #+#             */
/*   Updated: 2018/06/14 19:20:17 by oshvorak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/corewar_vm.h"

unsigned int	write_arg(t_process *pr, t_game *game, int tt, int pc)
{
	unsigned int tmp;

	if (tt == T_DIR)
		return (write_4_bytes(game, pc));
	else if (tt == T_IND)
	{
		tmp = write_2_bytes(game, pc);
		return (write_4_bytes(game, (pc + (short)tmp) % MEM_SIZE));
	}
	else
	{
		tmp = game->area[pc].value;
		return (pr->reg_num[(unsigned char)tmp - 1]);
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

void			op_and(t_game *game, t_process *pr)
{
	int				pc_buf;
	unsigned int	arg1;
	unsigned int	arg2;
	unsigned int	arg3;

	if (!check_codege(pr->op_id, game->area[(pr->pc + 1) % MEM_SIZE].value))
	{
		game->area[pr->pc].pc = 0;
		pr->pc += jump_pc(game->area[pr->pc + 1].value, pr->op_id);
		pr->pc %= MEM_SIZE;
		pr->op_id = 16;
		return ;
	}
	pc_buf = 2;
	arg1 = write_arg(pr, game, ret_arg(game->area[(pr->pc + 1) % MEM_SIZE].value,
		MASK_1, 6), (pr->pc + pc_buf) % MEM_SIZE);
	pc_buf += plus_pc(game->area[(pr->pc + 1) % MEM_SIZE].value, MASK_1, 6);
	arg2 = write_arg(pr, game, ret_arg(game->area[(pr->pc + 1) % MEM_SIZE].value,
		MASK_2, 4), (pr->pc + pc_buf) % MEM_SIZE);
	pc_buf += plus_pc(game->area[(pr->pc + 1) % MEM_SIZE].value, MASK_2, 4);
	arg3 = game->area[(pr->pc + pc_buf) % MEM_SIZE].value;
	pc_buf += 1;
	pr->reg_num[arg3 - 1] = arg1 & arg2;
	pr->carry = (pr->reg_num[arg3 - 1] == 0) ? 1 : 0;
	game->area[pr->pc].pc = 0;
	pr->pc += pc_buf;
	pr->pc %= MEM_SIZE;
}
