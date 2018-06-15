/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_add.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oshvorak <oshvorak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/12 15:22:35 by oshvorak          #+#    #+#             */
/*   Updated: 2018/06/15 20:23:12 by oshvorak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/corewar_vm.h"

int     wrong_codage(t_game *game, t_process *p)
{
	game->area[p->pc].pc = 0;
	p->pc += jump_pc(game->area[(p->pc + 1) % MEM_SIZE].value, \
		p->op_id);
	p->pc %= MEM_SIZE;
	p->op_id = 16;
	return (1);
}

int		checking_regs(t_game *game, t_process *p, int i)
{
	if (!check_reg_ind(game->area[(p->pc + i) % MEM_SIZE].value))
		return (0);
	if (!check_reg_ind(game->area[(p->pc + i + 1) % MEM_SIZE].value))
		return (0);
	if (!check_reg_ind(game->area[(p->pc + i + 2) % MEM_SIZE].value))
		return (0);
	return (1);
}

void	op_add(t_game *game, t_process *p)
{
	if (!check_codege(p->op_id, game->area[(p->pc + 1) % MEM_SIZE].value))
		if (wrong_codage(game, p))
			return ;
	if (checking_regs(game, p, 2))
	{
		p->reg_num[game->area[(p->pc + 4) % MEM_SIZE].value - 1] = \
		p->reg_num[game->area[(p->pc + 2) % MEM_SIZE].value - 1] \
		+ p->reg_num[game->area[(p->pc + 3) % MEM_SIZE].value - 1];
		if (p->reg_num[game->area[(p->pc + 4) % MEM_SIZE].value - 1] == 0)
			p->carry = 1;
		else
			p->carry = 0;
	}
	game->area[p->pc].pc = 0;
	p->pc = (p->pc + 5);
}
