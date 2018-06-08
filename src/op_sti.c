/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_sti.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oshvorak <oshvorak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/02 12:47:38 by oshvorak          #+#    #+#             */
/*   Updated: 2018/06/04 11:06:50 by oshvorak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/corewar_vm.h"

void	op_sti(t_game *game, t_process *process)
{
	unsigned int	arg2;
	unsigned int	arg3;
	int 			PC_jump;
	unsigned int    tmp;

	PC_jump = 3;
	if (!check_codege(process->op_id, game->area[process->PC + 1].value))
		return ;
	if (ret_arg(game->area[process->PC + 1].value, MASK_2, 4) == T_DIR)
	{
		arg2 = write_2_bytes(game, process->PC + 3);
		PC_jump += 2;
	}
	else if (ret_arg(game->area[process->PC + 1].value, MASK_2, 4) == T_IND)
	{
		arg2 = write_4_bytes(game, game->area[process->PC + 3].value % IDX_MOD);
		PC_jump += 2;
	}
	else
	{
		arg2 = process->REG_NUM[game->area[process->PC + 3].value - 1];
		PC_jump += 1;
	}
	if (ret_arg(game->area[process->PC + 1].value, MASK_3, 2) == T_DIR)
	{
		arg3 = write_2_bytes(game, PC_jump + process->PC);
		PC_jump += 2;
	}
	else
	{
		arg3 = process->REG_NUM[game->area[process->PC + PC_jump].value - 1];
		PC_jump++;
	}
	tmp = (process->PC + ((arg2 + arg3)));
	//ft_printf("arg2 %d\n", arg2);
	//ft_printf("arg3 %d\n", arg3);
	//ft_printf("tmp %d\n", tmp);
	if (tmp > 4095)
		tmp %= 4096;
	game->area[tmp].value = 0;
	game->area[tmp + 1].value = 0;
	game->area[tmp + 2].value = 0;
	game->area[tmp + 3].value = 0;
	game->area[tmp].value |= process->REG_NUM[game->area[process->PC + 2].value - 1] >> 24;
	game->area[tmp + 1].value |= process->REG_NUM[game->area[process->PC + 2].value - 1] >> 16;
	game->area[tmp + 2].value |= process->REG_NUM[game->area[process->PC + 2].value - 1] >> 8;
	game->area[tmp + 3].value |= process->REG_NUM[game->area[process->PC + 2].value - 1];
	
	process->REG_NUM[game->area[process->PC + 2].value - 1] = 0;

	game->area[tmp].color = game->area[process->PC].color;
	game->area[tmp + 1].color = game->area[process->PC].color;
	game->area[tmp + 2].color = game->area[process->PC].color;
	game->area[tmp + 3].color = game->area[process->PC].color;
	game->area[process->PC].PC = 0;
	process->PC += PC_jump;
}
