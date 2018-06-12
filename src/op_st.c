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
	game->area[tmp].value = 0;
	game->area[tmp + 1].value = 0;
	game->area[tmp + 2].value = 0;
	game->area[tmp + 3].value = 0;
	game->area[tmp].value |= pr->reg_num[game->area[pr->pc \
	+ 2].value] >> 24;
	game->area[tmp + 1].value |= pr->reg_num[game->area[pr->pc \
	+ 2].value] >> 16;
	game->area[tmp + 2].value |= pr->reg_num[game->area[pr->pc \
	+ 2].value] >> 8;
	game->area[tmp + 3].value |= pr->reg_num[game->area[pr->pc \
	+ 2].value];
	game->area[tmp].color = pr->color;
	game->area[tmp + 1].color = pr->color;
	game->area[tmp + 2].color = pr->color;
	game->area[tmp + 3].color = pr->color;
	game->area[tmp].bold = 20;
	game->area[tmp + 1].bold = 20;
	game->area[tmp + 2].bold = 20;
	game->area[tmp + 3].bold = 20;
}

static	int		else_if(t_game *game, t_process *pr, int *pc_jump)
{
	if (!check_reg_ind(game, pr, game->area[pr->pc + 3].value))
		return (0);
	pr->reg_num[game->area[pr->pc + 3].value - 1] = \
	pr->reg_num[game->area[pr->pc + 2].value - 1];
	*pc_jump += 1;
	return (1);
}

void			op_st(t_game *game, t_process *pr)
{
	unsigned int	arg2;
	int				pc_jump;
	unsigned int	tmp;

	pc_jump = 3;
	if (!check_codege(pr->op_id, game->area[pr->pc + 1].value))
	{
		game->area[pr->pc].pc = 0;
		pr->pc += jump_pc(game->area[pr->pc + 1].value, pr->op_id);
		pr->op_id = 16;
		return ;
	}
	if (ret_arg(game->area[pr->pc + 1].value, MASK_2, 4) == T_IND)
	{
		arg2 = write_2_bytes(game, pr->pc + 3);
		pc_jump += 2;
		tmp = (pr->pc + ((short)arg2 % IDX_MOD)) % MEM_SIZE;
		if (!check_reg_ind(game, pr, game->area[pr->pc + 2].value))
			return ;
		set_value(game, pr, tmp);
	}
	else if (ret_arg(game->area[pr->pc + 1].value, MASK_2, 4) == T_REG)
		if (else_if(game, pr, &pc_jump) == 0)
			return ;
	(pr->pc += pc_jump) && (game->area[pr->pc].pc = 0);
}
