/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_ld.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oshvorak <oshvorak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/07 11:52:06 by oshvorak          #+#    #+#             */
/*   Updated: 2018/06/13 19:42:49 by oshvorak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/corewar_vm.h"

static	unsigned int	ret_t_reg(t_game *game, t_process *process)
{
	unsigned int	t_reg;
	unsigned int	t_ind;
	unsigned int	arg_ind;

	if (ret_arg(game->area[process->pc + 1].value, MASK_1, 6) == T_DIR)
	{
		t_reg = game->area[process->pc + 6].value;
		process->reg_num[(unsigned char)t_reg - 1] = \
		write_4_bytes(game, process->pc + 2);
		game->area[process->pc].pc = 0;
		process->pc += 7;
	}
	else
	{
		t_reg = game->area[process->pc + 4].value;
		t_ind = write_2_bytes(game, process->pc + 2) % IDX_MOD;
		arg_ind = write_4_bytes(game, process->pc + (short)t_ind);
		process->reg_num[t_reg - 1] = arg_ind;
		game->area[process->pc].pc = 0;
		process->pc += 5;
	}
	return (t_reg);
}

void					op_ld(t_game *game, t_process *process)
{
	unsigned int	t_reg;

	if (!check_codege(process->op_id, game->area[process->pc + 1].value))
	{
		game->area[process->pc].pc = 0;
		process->pc += jump_pc(game->area[process->pc + 1].value, \
		process->op_id);
		process->op_id = 16;
		return ;
	}
	t_reg = ret_t_reg(game, process);
	//ft_printf("%u\n", process->reg_num[t_reg - 1]);
	process->carry = process->reg_num[t_reg - 1] == 0 ? 1 : 0;
}
