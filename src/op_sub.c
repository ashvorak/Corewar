/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_sub.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oshvorak <oshvorak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/12 16:00:29 by dlytvyn           #+#    #+#             */
/*   Updated: 2018/06/15 17:47:09 by oshvorak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/corewar_vm.h"

void	op_sub(t_game *game, t_process *p)
{
	if (!check_codege(p->op_id, game->area[(p->pc + 1) % MEM_SIZE].value))
	{
		game->area[p->pc].pc = 0;
		p->pc += jump_pc(game->area[(p->pc + 1) % MEM_SIZE].value, \
		p->op_id);
		p->pc %= MEM_SIZE;
		p->op_id = 16;
		return ;
	}
	if (checking_regs(game, p, 2))
	{
		p->reg_num[game->area[(p->pc + 4) % MEM_SIZE].value - 1] = \
		p->reg_num[game->area[(p->pc + 2) % MEM_SIZE].value - 1] \
		- p->reg_num[game->area[(p->pc + 3) % MEM_SIZE].value - 1];
		if (p->reg_num[game->area[(p->pc + 4) % MEM_SIZE].value - 1] == 0)
			p->carry = 1;
		else
			p->carry = 0;
	}
	game->area[p->pc].pc = 0;
	p->pc = (p->pc + 5);
}
