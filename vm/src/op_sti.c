/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_sti.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oshvorak <oshvorak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/02 12:47:38 by oshvorak          #+#    #+#             */
/*   Updated: 2018/06/15 20:30:43 by oshvorak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/corewar_vm.h"

int				check_reg_ind(int in)
{
	if (in > 0 && in < 17)
		return (1);
	else
		return (0);
}

static void		set_value(t_game *game, t_process *process, unsigned int tmp)
{
	int				i;
	int				num;
	unsigned int	mem;
	unsigned int	nem;

	i = 0;
	num = 24;
	nem = process->reg_num[game->area[(process->pc + 2) % MEM_SIZE].value - 1];
	while (i < 4)
	{
		mem = nem;
		game->area[(tmp + i) % MEM_SIZE].value = 0;
		game->area[(tmp + i) % MEM_SIZE].value |= mem >> num;
		game->area[(tmp + i) % MEM_SIZE].bold = 20;
		game->area[(tmp + i) % MEM_SIZE].color = process->color;
		i++;
		num -= 8;
	}
	game->area[process->pc].pc = 0;
}

unsigned int	second_arg(t_game *game, t_process *pr, int *jump, int *er)
{
	if (ret_arg(game->area[(pr->pc + 1) % MEM_SIZE].value, MASK_2, 4) == T_REG)
	{
		*jump = *jump + 4;
		if (check_reg_ind(game->area[(pr->pc + 3) % MEM_SIZE].value))
			return (pr->reg_num[game->area[(pr->pc + 3) % MEM_SIZE].value - 1]);
		else
		{
			*er = 1;
			return (0);
		}
	}
	else if (ret_arg(game->area[(pr->pc + 1) % MEM_SIZE].value, MASK_2, 4)
		== T_IND)
	{
		*jump = *jump + 5;
		return (write_4_bytes(game, ((pr->pc + (((short)write_2_bytes(game,
			(pr->pc + 3) % MEM_SIZE)) % IDX_MOD)) % MEM_SIZE)));
	}
	else
	{
		*jump = *jump + 5;
		return ((short)write_2_bytes(game, (pr->pc + 3) % MEM_SIZE));
	}
}

unsigned int	third_arg(t_game *game, t_process *pr, int *jump, int *er)
{
	unsigned int res;

	if (ret_arg(game->area[(pr->pc + 1) % MEM_SIZE].value, MASK_3, 2) == T_REG)
	{
		if (check_reg_ind(game->area[(pr->pc + *jump) % MEM_SIZE].value))
			res = pr->reg_num[game->area[(pr->pc + *jump) %
			MEM_SIZE].value - 1];
		else
		{
			*er = 1;
			res = 0;
		}
		*jump = *jump + 1;
		return (res);
	}
	else
	{
		res = (short)write_2_bytes(game, (pr->pc + *jump) % MEM_SIZE);
		*jump = *jump + 2;
		return (res);
	}
}

void			op_sti(t_game *game, t_process *pr)
{
	int		arg2;
	int		arg3;
	int		jump;
	int		er;

	er = 0;
	if (!check_codege(pr->op_id, game->area[(pr->pc + 1) % MEM_SIZE].value))
		if (wrong_codage(game, pr))
			return ;
	jump = 0;
	arg2 = second_arg(game, pr, &jump, &er);
	arg3 = third_arg(game, pr, &jump, &er);
	(er == 0) ? set_value(game, pr, (pr->pc + (arg2 + arg3) % IDX_MOD)
		% MEM_SIZE) : 0;
	game->area[pr->pc].pc = 0;
	pr->pc += jump;
	pr->pc %= MEM_SIZE;
}
