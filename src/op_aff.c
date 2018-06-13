/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_aff.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oshvorak <oshvorak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/02 12:47:38 by oshvorak          #+#    #+#             */
/*   Updated: 2018/06/12 15:42:41 by oshvorak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/corewar_vm.h"

void	op_aff(t_game *game, t_process *process)
{
	if (!check_codege(process->op_id, game->area[process->pc + 1].value))
	{
		game->area[process->pc].pc = 0;
		process->pc += jump_pc(game->area[process->pc + 1].value, \
		process->op_id);
		process->op_id = 16;
		return ;
	}
	game->area[process->pc].pc = 0;
	process->pc += 3;
	ft_printf("%c\n", process->reg_num[game->area[process->pc + 2].value] \
	% 256);
}
