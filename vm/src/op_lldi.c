/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_lldi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oshvorak <oshvorak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/07 11:52:06 by oshvorak          #+#    #+#             */
/*   Updated: 2018/06/15 20:31:32 by oshvorak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/corewar_vm.h"

static void			ret_arg1_add(t_game *game, t_process *p, unsigned int *arg1)
{
	if (check_reg_ind(game->area[(p->pc + 2) % MEM_SIZE].value))
		*arg1 = p->reg_num[game->area[(p->pc + 2) % MEM_SIZE].value - 1];
	else
	{
		*arg1 = 0;
		game->er = 1;
	}
	p->pc = (p->pc + 3) % MEM_SIZE;
}

static unsigned	int	ret_arg1(t_game *game, t_process *p, unsigned int codage)
{
	unsigned int	arg1;
	unsigned int	t_ind;

	if (ret_arg(codage, MASK_1, 6) == T_DIR)
	{
		arg1 = (short)write_2_bytes(game, (p->pc + 2) % MEM_SIZE);
		p->pc = (p->pc + 4) % MEM_SIZE;
	}
	else if (ret_arg(game->area[(p->pc + 1) % MEM_SIZE].value, MASK_1, 6) ==
		T_IND)
	{
		t_ind = (short)write_2_bytes(game, (p->pc + 2) % MEM_SIZE);
		arg1 = write_4_bytes(game, ((t_ind % IDX_MOD) + p->pc) % MEM_SIZE);
		p->pc = (p->pc + 4) % MEM_SIZE;
	}
	else
		ret_arg1_add(game, p, &arg1);
	return (arg1);
}

static unsigned int	ret_arg2(t_game *game, t_process *p, unsigned int codage)
{
	unsigned int	arg2;

	if (ret_arg(codage, MASK_2, 4) == T_DIR)
	{
		arg2 = write_2_bytes(game, p->pc);
		arg2 = (short)arg2;
		p->pc = (p->pc + 2) % MEM_SIZE;
	}
	else
	{
		if (check_reg_ind(game->area[p->pc].value))
			arg2 = p->reg_num[game->area[p->pc].value - 1];
		else
		{
			arg2 = 0;
			game->er = 1;
		}
		p->pc = (p->pc + 1) % MEM_SIZE;
	}
	return (arg2);
}

void				op_lldi(t_game *game, t_process *p)
{
	unsigned int	arg1;
	unsigned int	arg2;
	unsigned int	arg3;
	unsigned int	codage;
	int				pc_buf;

	if (!check_codege(p->op_id, game->area[p->pc + 1].value))
		if (wrong_codage(game, p))
			return ;
	pc_buf = p->pc;
	codage = game->area[(p->pc + 1) % MEM_SIZE].value;
	game->area[p->pc].pc = 0;
	arg1 = ret_arg1(game, p, codage);
	arg2 = ret_arg2(game, p, codage);
	arg3 = game->area[p->pc++].value;
	p->pc %= MEM_SIZE;
	if (check_reg_ind(arg3) && game->er == 0)
	{
		p->reg_num[arg3 - 1] = write_4_bytes(game, (((int)arg1 \
	+ (int)arg2) + pc_buf) % MEM_SIZE);
		p->carry = (p->reg_num[arg3 - 1] == 0) ? 1 : 0;
	}
	game->er = 0;
}
