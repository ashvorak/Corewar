/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_st.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlytvyn <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/12 16:37:25 by dlytvyn           #+#    #+#             */
/*   Updated: 2018/06/12 16:37:26 by dlytvyn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/corewar_vm.h"

void           set_value(t_game *game, t_process *pr, unsigned int in)
{
	int i;
	int num;
	
	i = 0;
	num = 24;
	if (!check_reg_ind(game, pr, game->area[(pr->pc + 2) % MEM_SIZE].value))
		return ;
	while (i < 4)
	{
		game->area[(in + i) % MEM_SIZE].value = 0;
		game->area[(in + i) % MEM_SIZE].value |= pr->reg_num[game->area[(pr->pc \
			+ 2) % MEM_SIZE].value - 1] >> num;
		game->area[(in + i) % MEM_SIZE].color = pr->color;
		game->area[(in + i) % MEM_SIZE].bold = 20;
		i++;
		num -= 8;
	}
}

void			op_st(t_game *game, t_process *pr)
{
	int             t_ind;
	unsigned  int   arg2;
	
	if (!check_codege(pr->op_id, game->area[(pr->pc + 1) % MEM_SIZE].value))
	{
		game->area[pr->pc].pc = 0;
		pr->pc = (pr->pc + jump_pc(game->area[(pr->pc + 1) % MEM_SIZE].value, pr->op_id)) % MEM_SIZE;
		pr->op_id = 16;
		return ;
	}
	if (check_codege(pr->op_id, game->area[(pr->pc + 1)
	                                       % MEM_SIZE].value) == T_IND)
	{
		t_ind = write_2_bytes(game, (pr->pc + 3) % MEM_SIZE);
		arg2 = write_4_bytes(game, (pr->pc + t_ind) % MEM_SIZE);
		set_value(game, pr, (pr->pc + (arg2 % IDX_MOD)) % MEM_SIZE);
		game->area[pr->pc].pc = 0;
		pr->pc = (pr->pc + 5) % MEM_SIZE;
	}
	else if (check_codege(pr->op_id, game->area[(pr->pc + 1)
	                                            % MEM_SIZE].value) == T_REG)
	{
		if (check_reg_ind(game, pr, game->area[(pr->pc + 3) % MEM_SIZE].value))
			pr->reg_num[(game->area[(pr->pc + 3)].value) - 1] = pr->reg_num[(game->area[pr->pc + 2].value) - 1];
		game->area[pr->pc].pc = 0;
		pr->pc = (pr->pc + 4) % MEM_SIZE;
	}
}
