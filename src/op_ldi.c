/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_ldi.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oshvorak <oshvorak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/07 11:52:06 by oshvorak          #+#    #+#             */
/*   Updated: 2018/06/15 20:02:35 by oshvorak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/corewar_vm.h"

static int	ret_arg1(t_game *game, t_process *p, unsigned int codage)
{
	unsigned int	arg1;
	unsigned int	t_ind;

	if (ret_arg(codage, MASK_1, 6) == T_DIR)
	{
		arg1 = write_2_bytes(game, p->pc + 2);
		arg1 = (short)arg1;
		p->pc = (p->pc + 4) % MEM_SIZE;
	}
	else if (ret_arg(game->area[p->pc + 1].value, MASK_1, 6) == T_IND)
	{
		t_ind = write_2_bytes(game, (p->pc + 2) % MEM_SIZE);
		arg1 = write_4_bytes(game, ((short)t_ind + p->pc) % MEM_SIZE) % IDX_MOD;
		p->pc = (p->pc + 4) % MEM_SIZE;
	}
	else
	{
		if (check_reg_ind(game, p, game->area[p->pc + 2].value))
			arg1 = p->reg_num[game->area[p->pc + 2].value - 1];
		else
		{
			game->er = 1;
			arg1 = 0;
		}
		p->pc = (p->pc + 3) % MEM_SIZE;
	}
	return (arg1);
}

static int	ret_arg2(t_game *game, t_process *p, unsigned int codage)
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
		if (check_reg_ind(game, p, game->area[p->pc].value))
			arg2 = p->reg_num[game->area[p->pc].value - 1];
		else
		{
			game->er = 1;
			arg2 = 0;
		}
		p->pc = (p->pc + 1) % MEM_SIZE;
	}
	return (arg2);
}

void		op_ldi(t_game *game, t_process *p)
{
	unsigned int	arg1;
	unsigned int	arg2;
	unsigned int	arg3;
	unsigned int	codage;
	int				pc_buf;

	if (!check_codege(p->op_id, game->area[(p->pc + 1) % MEM_SIZE].value))
	{
		game->area[p->pc].pc = 0;
		p->pc += jump_pc(game->area[(p->pc + 1) % MEM_SIZE].value, \
		p->op_id);
		p->op_id = 16;
		return ;
	}
	pc_buf = p->pc;
	codage = game->area[(p->pc + 1) % MEM_SIZE].value;
	game->area[p->pc].pc = 0;
	arg1 = (unsigned int)ret_arg1(game, p, codage);
	arg2 = (unsigned int)ret_arg2(game, p, codage);
	arg3 = game->area[p->pc++].value;
	p->pc %= MEM_SIZE;
	if (check_reg_ind(game, p, arg3) && game->er == 0)
		p->reg_num[arg3 - 1] = write_4_bytes(game, ((((int)arg1 \
	+ (int)arg2) % IDX_MOD) % MEM_SIZE + pc_buf) % MEM_SIZE);
	game->er = 0;
}
