/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_ld.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oshvorak <oshvorak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/07 11:52:06 by oshvorak          #+#    #+#             */
/*   Updated: 2018/06/13 21:44:27 by oshvorak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/corewar_vm.h"

static	unsigned int	ret_t_reg(t_game *game, t_process *process)
{
	unsigned int	t_reg;
	int	            t_ind;
	
	if (ret_arg(game->area[(process->pc + 1) % MEM_SIZE].value, MASK_1, 6) == T_DIR)
	{
		t_reg = game->area[(process->pc + 6) % MEM_SIZE].value;
		process->reg_num[(unsigned char)t_reg - 1] = \
		write_4_bytes(game, (process->pc + 2) % MEM_SIZE);
		game->area[process->pc].pc = 0;
		process->pc = (process->pc + 7) % MEM_SIZE;
	}
	else
	{
		t_reg = game->area[(process->pc + 4) % MEM_SIZE].value;
		t_ind = (short)write_2_bytes(game, (process->pc + 2)) % MEM_SIZE;
		process->reg_num[t_reg - 1] = write_4_bytes(game, (t_ind + process->pc) % MEM_SIZE);
		game->area[process->pc].pc = 0;
		process->pc = (process->pc + 5) % MEM_SIZE;
	}
	return (t_reg);
}

void					op_ld(t_game *game, t_process *process)
{
	unsigned int	t_reg;

	if (!check_codege(process->op_id, game->area[(process->pc + 1) % MEM_SIZE].value))
	{
		game->area[process->pc].pc = 0;
		process->pc += jump_pc(game->area[(process->pc + 1) % MEM_SIZE].value, \
		process->op_id);
		process->op_id = 16;
		return ;
	}
	t_reg = ret_t_reg(game, process);
	process->carry = process->reg_num[t_reg - 1] == 0 ? 1 : 0;
}
