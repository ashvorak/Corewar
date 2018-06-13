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

static	void	set_value(t_game *game, t_process *pr, unsigned int tmp)
{
	game->area[tmp % MEM_SIZE].value = 0;
	game->area[(tmp + 1) % MEM_SIZE].value = 0;
	game->area[(tmp + 2) % MEM_SIZE].value = 0;
	game->area[(tmp + 3) % MEM_SIZE].value = 0;
	game->area[tmp % MEM_SIZE].value |= pr->reg_num[game->area[(pr->pc \
	+ 2) % MEM_SIZE].value] >> 24;
	game->area[(tmp + 1) % MEM_SIZE].value |= pr->reg_num[game->area[(pr->pc \
	+ 2) % MEM_SIZE].value] >> 16;
	game->area[(tmp + 2) % MEM_SIZE].value |= pr->reg_num[game->area[(pr->pc \
	+ 2) % MEM_SIZE].value] >> 8;
	game->area[(tmp + 3) % MEM_SIZE].value |= pr->reg_num[game->area[(pr->pc \
	+ 2) % MEM_SIZE].value];
	game->area[tmp % MEM_SIZE].color = pr->color;
	game->area[(tmp + 1) % MEM_SIZE].color = pr->color;
	game->area[(tmp + 2) % MEM_SIZE].color = pr->color;
	game->area[(tmp + 3) % MEM_SIZE].color = pr->color;
	game->area[tmp % MEM_SIZE].bold = 20;
	game->area[(tmp + 1) % MEM_SIZE].bold = 20;
	game->area[(tmp + 2) % MEM_SIZE].bold = 20;
	game->area[(tmp + 3) % MEM_SIZE].bold = 20;
}

static	int		else_if(t_game *game, t_process *pr, int *pc_jump)
{
	if (!check_reg_ind(game, pr, game->area[(pr->pc + 3) % MEM_SIZE].value))
		return (0);
	pr->reg_num[game->area[(pr->pc + 3) % MEM_SIZE].value - 1] = \
	pr->reg_num[game->area[(pr->pc + 2) % MEM_SIZE].value - 1];
	*pc_jump += 1;
	return (1);
}

void			op_st(t_game *game, t_process *pr)
{
	unsigned int	arg2;
	int				pc_jump;
	unsigned int	tmp;

	pc_jump = 3;
	if (!check_codege(pr->op_id, game->area[(pr->pc + 1) % MEM_SIZE].value))
	{
		game->area[pr->pc].pc = 0;
		pr->pc = (pr->pc + jump_pc(game->area[(pr->pc + 1) % MEM_SIZE].value, pr->op_id)) % MEM_SIZE;
		pr->op_id = 16;
		return ;
	}
	if (ret_arg(game->area[(pr->pc + 1) % MEM_SIZE].value, MASK_2, 4) == T_IND)
	{
		arg2 = write_2_bytes(game, (pr->pc + 3) % MEM_SIZE);
		pc_jump += 2;
		tmp = (pr->pc + ((short)arg2 % IDX_MOD)) % MEM_SIZE;
		if (!check_reg_ind(game, pr, game->area[(pr->pc + 2) % MEM_SIZE].value))
			return ;
		set_value(game, pr, tmp);
	}
	else if (ret_arg(game->area[(pr->pc + 1) % MEM_SIZE].value, MASK_2, 4) == T_REG)
		if (else_if(game, pr, &pc_jump) == 0)
			return ;
	(pr->pc = (pr->pc + pc_jump) % MEM_SIZE) && (game->area[pr->pc].pc = 0);
}
