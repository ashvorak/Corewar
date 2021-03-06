/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_lld.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oshvorak <oshvorak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/07 11:52:06 by oshvorak          #+#    #+#             */
/*   Updated: 2018/06/15 20:29:58 by oshvorak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/corewar_vm.h"

static	unsigned int	ret_t_reg(t_game *game, t_process *p)
{
	unsigned int	t_reg;
	int				t_ind;

	game->area[p->pc].pc = 0;
	if (ret_arg(game->area[(p->pc + 1) % MEM_SIZE].value, MASK_1, 6) == T_DIR)
	{
		t_reg = game->area[(p->pc + 6) % MEM_SIZE].value;
		write_reg(game, t_reg, p);
		p->pc = (p->pc + 7) % MEM_SIZE;
	}
	else
	{
		t_reg = game->area[(p->pc + 4) % MEM_SIZE].value;
		t_ind = write_2_bytes(game, (p->pc + 2)) % MEM_SIZE;
		if (check_reg_ind(t_reg))
			p->reg_num[t_reg - 1] = \
			write_4_bytes(game, (((short)t_ind) + p->pc) % MEM_SIZE);
		else
			game->er = 1;
		p->pc = (p->pc + 5) % MEM_SIZE;
	}
	return (t_reg);
}

void					op_lld(t_game *game, t_process *p)
{
	unsigned int	t_reg;

	if (!check_codege(p->op_id, game->area[(p->pc + 1) % MEM_SIZE].value))
		if (wrong_codage(game, p))
			return ;
	t_reg = ret_t_reg(game, p);
	if (check_reg_ind(t_reg) && game->er == 0)
		p->carry = p->reg_num[t_reg - 1] == 0 ? 1 : 0;
	game->er = 0;
}
