/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_ld.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oshvorak <oshvorak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/07 11:52:06 by oshvorak          #+#    #+#             */
/*   Updated: 2018/06/07 13:04:47 by oshvorak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/corewar_vm.h"

void    op_ld(t_game *game, t_process *process)
{
	int		t_reg;
	int 	t_ind;

	if (!check_codege(process->op_id, game->area[process->PC + 1].value))
		return ;
	if (ret_arg(game->area[process->PC + 1].value, MASK_1, 6) == T_DIR)
	{
		t_reg = game->area[process->PC + 6].value;
		process->REG_NUM[t_reg - 1] = write_4_bytes(game, process->PC + 2);
		game->area[process->PC].PC = 0;
		process->PC += 7;
	}
	else
	{
		t_reg = game->area[process->PC + 3].value;
		t_ind = write_2_bytes(game, process->PC + 2);
		process->REG_NUM[t_reg - 1] = write_2_bytes(game, process->PC + t_ind);
		game->area[process->PC].PC = 0;
		process->PC += 5;
	}
	process->carry = game->process->REG_NUM[t_reg] == 0 ? 1 : 0;
}
