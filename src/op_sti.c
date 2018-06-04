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
	int 			PC_buf;

	if (!check_codege(process->op_id, game->area[process->PC + 1].value))
		return ;
	if (ret_arg(game->area[process->PC + 1].value, MASK_2, 4) == T_DIR)
	{
		arg2 = write_2_bytes(game, process->PC, 3);
		PC_buf = process->PC + 4;
	}
	else
	{
		arg2 = write_4_bytes(game, process->PC, 3);
		arg2 %= IDX_MOD;
		PC_buf = process->PC + 6;
	}
	if (ret_arg(game->area[process->PC + 1].value, MASK_3, 2) == T_DIR)
		arg3 = write_2_bytes(game, PC_buf, 1);
	else
		arg3 = game->area[PC_buf + 1].value;
	game->area[(process->PC + arg2 + arg3) % IDX_MOD] = game->area[process->PC + 2];
}
