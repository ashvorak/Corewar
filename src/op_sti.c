/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_sti.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oshvorak <oshvorak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/02 12:47:38 by oshvorak          #+#    #+#             */
/*   Updated: 2018/06/14 15:23:17 by oshvorak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/corewar_vm.h"

int				check_reg_ind(t_game *game, t_process *process, int in)
{
	if (in > 0 && in < 17)
		return (1);
	else
	{
		game->area[process->pc].pc = 0;
		process->pc += jump_pc(game->area[process->pc + 1].value,
			process->op_id);
		process->op_id = 16;
		return (0);
	}
}

static void		set_value(t_game *game, t_process *process, unsigned int tmp)
{
	int i;
	int num;
	unsigned int mem;
	unsigned int nem;

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
		num -=8;
	}
	game->area[process->pc].pc = 0;
}


unsigned int    second_arg(t_game *game, t_process *pr, int *jump)
{
	unsigned int t_ind;
	
	t_ind = 0;
	if (ret_arg(game->area[(pr->pc + 1) % MEM_SIZE].value, MASK_2, 4) == T_REG)
	{
		*jump = *jump + 4;
		//if (!check_reg_ind(game, pr, game->area[(pr->pc + 3) % MEM_SIZE].value))
		//	return (-1);
		return (pr->reg_num[game->area[(pr->pc + 3) % MEM_SIZE].value - 1]);
	}
	else if (ret_arg(game->area[(pr->pc + 1) % MEM_SIZE].value, MASK_2, 4) == T_IND)
	{
		t_ind = (short)write_2_bytes(game, (pr->pc + 3) % MEM_SIZE);
		*jump = *jump + 5;
		t_ind = write_4_bytes(game, ((pr->pc + t_ind) % IDX_MOD)) % MEM_SIZE;
		return (t_ind);
	}
	else
	{
		*jump = *jump + 5;
		return ((short)write_2_bytes(game, (pr->pc + 3) % MEM_SIZE));
	}
}

unsigned int    third_arg(t_game *game, t_process *pr, int *jump)
{
	unsigned int res;
	if (ret_arg(game->area[(pr->pc + 1) % MEM_SIZE].value, MASK_3, 2) == T_REG)
	{
		res = pr->reg_num[game->area[(pr->pc + *jump) % MEM_SIZE].value - 1];
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

void            op_sti(t_game *game, t_process *pr)
{
	int    arg2;
	int    arg3;
	int    jump;
	
	if (!check_codege(pr->op_id, game->area[(pr->pc + 1) % MEM_SIZE].value))
	{
		game->area[pr->pc].pc = 0;
		pr->pc = (pr->pc + jump_pc(game->area[(pr->pc + 1) % MEM_SIZE].value, pr->op_id)) % MEM_SIZE;
		pr->op_id = 16;
		return ;
	}
	jump = 0;
	arg2 = second_arg(game, pr, &jump);
	arg3 = third_arg(game, pr, &jump);
	set_value(game, pr, (pr->pc + ((int)arg2 + (int)arg3) % IDX_MOD) % MEM_SIZE);
	pr->pc += jump;
	pr->pc %= MEM_SIZE;
}
