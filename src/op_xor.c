/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_xor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oshvorak <oshvorak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/12 15:54:04 by dlytvyn           #+#    #+#             */
/*   Updated: 2018/06/13 14:40:19 by oshvorak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/corewar_vm.h"

void	op_xor(t_game *game, t_process *pr)
{
	int				pc_buf;
	unsigned int	arg1;
	unsigned int	arg2;
	unsigned int	arg3;

	if (!check_codege(pr->op_id, game->area[(pr->pc + 1) % MEM_SIZE].value))
	{
		game->area[pr->pc].pc = 0;
		pr->pc += jump_pc(game->area[(pr->pc + 1) % MEM_SIZE].value, pr->op_id);
		pr->op_id = 16;
		return ;
	}
	pc_buf = 2;
	arg1 = write_arg(pr, game,
		ret_arg(game->area[(pr->pc + 1) % MEM_SIZE].value, MASK_1, 6), (pr->pc + pc_buf) % MEM_SIZE);
	pc_buf += plus_pc(game->area[(pr->pc + 1) % MEM_SIZE].value, MASK_1, 6);
	arg2 = write_arg(pr, game,
		ret_arg(game->area[(pr->pc + 1) % MEM_SIZE].value, MASK_2, 4), (pr->pc + pc_buf) % MEM_SIZE);
	pc_buf += plus_pc(game->area[(pr->pc + 1) % MEM_SIZE].value, MASK_2, 4);
	arg3 = game->area[(pr->pc + pc_buf) % MEM_SIZE].value;
	pc_buf += 1;
	pr->reg_num[arg3 - 1] = arg1 ^ arg2;
	pr->carry = (pr->reg_num[arg3 - 1] == 0) ? 1 : 0;
	game->area[pr->pc].pc = 0;
	pr->pc += pc_buf;
	pr->pc %= MEM_SIZE;
}
