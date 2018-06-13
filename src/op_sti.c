/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_sti.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oshvorak <oshvorak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/02 12:47:38 by oshvorak          #+#    #+#             */
/*   Updated: 2018/06/13 14:53:25 by oshvorak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/corewar_vm.h"

int				check_reg_ind(t_game *game, t_process *process, int in)
{
	if (in > 0 && in < 17)
		return (1);
	else
	{
		game->area[(process->pc) % MEM_SIZE].pc = 0;
		process->pc += jump_pc(game->area[(process->pc + 1) % MEM_SIZE].value,
			process->op_id);
		process->op_id = 16;
		return (0);
	}
}

static void		set_value(t_game *game, t_process *process, unsigned int tmp)
{
	game->area[(tmp) % MEM_SIZE].value = 0;
	game->area[(tmp + 1) % MEM_SIZE].value = 0;
	game->area[(tmp + 2) % MEM_SIZE].value = 0;
	game->area[(tmp + 3) % MEM_SIZE].value = 0;
	game->area[(tmp) % MEM_SIZE].value |= process->reg_num[game->area[(process->pc
		+ 2) % MEM_SIZE].value - 1] >> 24;
	game->area[(tmp + 1) % MEM_SIZE].value |= process->reg_num[game->area[(process->pc
		+ 2) % MEM_SIZE].value - 1] >> 16;
	game->area[(tmp + 2) % MEM_SIZE].value |= process->reg_num[game->area[(process->pc
		+ 2) % MEM_SIZE].value - 1] >> 8;
	game->area[(tmp + 3) % MEM_SIZE].value |= process->reg_num[game->area[(process->pc
		+ 2) % MEM_SIZE].value - 1];
	game->area[(tmp) % MEM_SIZE].bold = 20;
	game->area[(tmp + 1) % MEM_SIZE].bold = 20;
	game->area[(tmp + 2) % MEM_SIZE].bold = 20;
	game->area[(tmp + 3) % MEM_SIZE].bold = 20;
	game->area[(tmp) % MEM_SIZE].color = process->color;
	game->area[(tmp + 1) % MEM_SIZE].color = process->color;
	game->area[(tmp + 2) % MEM_SIZE].color = process->color;
	game->area[(tmp + 3) % MEM_SIZE].color = process->color;
	game->area[(process->pc) % MEM_SIZE].pc = 0;
}

static int		first_if(t_game *game, t_process *process,
	unsigned int *arg2, int *pc_jump)
{
	unsigned int	t_ind;

	t_ind = 0;
	if (ret_arg(game->area[(process->pc + 1) % MEM_SIZE].value, MASK_2, 4) == T_DIR)
	{
		*arg2 = write_2_bytes(game, (process->pc + 3) % MEM_SIZE);
		*arg2 = (short)*arg2;
		*pc_jump += 2;
	}
	else if (ret_arg(game->area[(process->pc + 1) % MEM_SIZE].value, MASK_2, 4) == T_IND)
	{
		t_ind = write_2_bytes(game, game->area[(process->pc + 3) % MEM_SIZE].value);
		*arg2 = write_4_bytes(game, t_ind % IDX_MOD);
		*pc_jump += 2;
	}
	else
	{
		if (!check_reg_ind(game, process, game->area[(process->pc + 3) % MEM_SIZE].value))
			return (0);
		*arg2 = process->reg_num[game->area[(process->pc + 3) % MEM_SIZE].value - 1];
		*pc_jump += 1;
	}
	return (1);
}

static int		second_if(t_game *game, t_process *process,
	unsigned int *arg3, int *pc_jump)
{
	if (ret_arg(game->area[(process->pc + 1) % MEM_SIZE].value, MASK_3, 2) == T_DIR)
	{
		*arg3 = write_2_bytes(game, (*pc_jump + process->pc) % MEM_SIZE);
		*arg3 = (short)*arg3;
		*pc_jump += 2;
	}
	else
	{
		if (!check_reg_ind(game, process, game->area[(process->pc +
			*pc_jump) % MEM_SIZE].value))
			return (0);
		*arg3 = process->reg_num[game->area[(process->pc + *pc_jump) % MEM_SIZE].value - 1];
		*pc_jump += 1;
	}
	return (1);
}

void			op_sti(t_game *game, t_process *process)
{
	unsigned int	arg2;
	unsigned int	arg3;
	int				pc_jump;
	unsigned int	tmp;

	pc_jump = 3;
	if (!check_codege(process->op_id, game->area[(process->pc + 1) % MEM_SIZE].value))
	{
		game->area[(process->pc) % MEM_SIZE].pc = 0;
		process->pc += jump_pc(game->area[(process->pc + 1) % MEM_SIZE].value, process->op_id);
		process->op_id = 16;
		return ;
	}
	if (!first_if(game, process, &arg2, &pc_jump))
		return ;
	if (!second_if(game, process, &arg3, &pc_jump))
		return ;
	tmp = ((process->pc + (((int)arg2 + (int)arg3) % IDX_MOD)) % MEM_SIZE);
	set_value(game, process, tmp);
	process->pc += pc_jump;
	process->pc %= MEM_SIZE;
}
