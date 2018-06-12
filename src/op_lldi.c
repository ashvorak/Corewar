/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_lldi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oshvorak <oshvorak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/07 11:52:06 by oshvorak          #+#    #+#             */
/*   Updated: 2018/06/09 18:25:43 by oshvorak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/corewar_vm.h"

static	int	first_if(t_game *game, t_process *process,
	unsigned int *arg1, int *t_ind)
{
	int	pc_buf;

	pc_buf = 0;
	if (ret_arg(game->area[process->PC + 1].value, MASK_1, 6) == T_DIR)
	{
		*arg1 = write_2_bytes(game, process->PC + 2);
		*arg1 = (short)arg1;
		pc_buf += 4;
	}
	else if (ret_arg(game->area[process->PC + 1].value, MASK_1, 6) == T_IND)
	{
		*t_ind = write_2_bytes(game, process->PC + 2);
		*arg1 = write_4_bytes(game, ((short)t_ind % IDX_MOD) + process->PC);
		pc_buf += 4;
	}
	else
	{
		*arg1 = process->REG_NUM[game->area[process->PC + 2].value - 1];
		pc_buf += 3;
	}
	return (pc_buf);
}

static	int	second_if(t_game *game, t_process *process, unsigned int *arg2)
{
	int	pc_buf;

	pc_buf = 0;
	if (ret_arg(game->area[process->PC + 1].value, MASK_2, 4) == T_DIR)
	{
		*arg2 = write_2_bytes(game, process->PC + pc_buf);
		*arg2 = (short)arg2;
		pc_buf += 2;
	}
	else
	{
		*arg2 = process->REG_NUM[game->area[process->PC + pc_buf].value - 1];
		pc_buf += 1;
	}
	return (pc_buf);
}

void		op_lldi(t_game *game, t_process *process)
{
	unsigned int	arg1;
	unsigned int	arg2;
	unsigned int	arg3;
	int				t_ind;
	int				pc_buf;

	if (!check_codege(process->op_id, game->area[process->PC + 1].value))
	{
		game->area[process->PC].PC = 0;
		process->PC += jump_pc(game->area[process->PC + 1].value,
			process->op_id);
		process->op_id = 16;
		return ;
	}
	pc_buf = 0;
	game->area[process->PC].PC = 0;
	pc_buf += first_if(game, process, &arg1, &t_ind);
	pc_buf += second_if(game, process, &arg2);
	arg3 = game->area[process->PC + pc_buf].value;
	pc_buf++;
	process->REG_NUM[arg3 - 1] = write_4_bytes(game,
		((arg1 + arg2)) + process->PC);
	process->PC += pc_buf;
}
