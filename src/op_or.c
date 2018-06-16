/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_or.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oshvorak <oshvorak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/12 16:02:46 by dlytvyn           #+#    #+#             */
/*   Updated: 2018/06/15 20:42:04 by oshvorak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/corewar_vm.h"

void	op_or(t_game *game, t_process *pr)
{
	int				pc_buf;
	unsigned int	arg1;
	unsigned int	arg2;
	unsigned int	arg3;

	if (!check_codege(pr->op_id, game->area[(pr->pc + 1) % MEM_SIZE].value))
		if (wrong_codage(game, pr))
			return ;
	pc_buf = 2;
	arg1 = write_arg(pr, game, ret_arg(game->area[(pr->pc + 1) %
		MEM_SIZE].value, MASK_1, 6), (pr->pc + pc_buf) % MEM_SIZE);
	pc_buf += plus_pc(game->area[(pr->pc + 1) % MEM_SIZE].value, MASK_1, 6);
	arg2 = write_arg(pr, game, ret_arg(game->area[(pr->pc + 1) %
		MEM_SIZE].value, MASK_2, 4), (pr->pc + pc_buf) % MEM_SIZE);
	pc_buf += plus_pc(game->area[(pr->pc + 1) % MEM_SIZE].value, MASK_2, 4);
	arg3 = game->area[(pr->pc + pc_buf) % MEM_SIZE].value;
	pc_buf += 1;
	if (check_reg_ind(arg3) && game->er == 0)
	{
		pr->reg_num[arg3 - 1] = arg1 | arg2;
		pr->carry = (pr->reg_num[arg3 - 1] == 0) ? 1 : 0;
	}
	game->area[pr->pc].pc = 0;
	pr->pc = (pr->pc + pc_buf) % MEM_SIZE;
	game->er = 0;
}
