/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_xor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlytvyn <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/12 15:54:04 by dlytvyn           #+#    #+#             */
/*   Updated: 2018/06/12 15:54:06 by dlytvyn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/corewar_vm.h"

void	op_xor(t_game *game, t_process *pr)
{
	int				pc_buf;
	unsigned int	arg1;
	unsigned int	arg2;
	unsigned int	arg3;

	if (!check_codege(pr->op_id, game->area[pr->PC + 1].value))
	{
		game->area[pr->PC].PC = 0;
		pr->PC += jump_pc(game->area[pr->PC + 1].value, pr->op_id);
		pr->op_id = 16;
		return ;
	}
	pc_buf = 2;
	arg1 = write_arg(pr, game,
		ret_arg(game->area[pr->PC + 1].value, MASK_1, 6), pr->PC + pc_buf);
	pc_buf += plus_PC(game->area[pr->PC + 1].value, MASK_1, 6);
	arg2 = write_arg(pr, game,
		ret_arg(game->area[pr->PC + 1].value, MASK_2, 4), pr->PC + pc_buf);
	pc_buf += plus_PC(game->area[pr->PC + 1].value, MASK_2, 4);
	arg3 = game->area[pr->PC + pc_buf].value;
	pc_buf += 1;
	pr->REG_NUM[arg3 - 1] = arg1 ^ arg2;
	pr->carry = (pr->REG_NUM[arg3 - 1] == 0) ? 1 : 0;
	game->area[pr->PC].PC = 0;
	pr->PC += pc_buf;
}
