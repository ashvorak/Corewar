/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_aff.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oshvorak <oshvorak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/02 12:47:38 by oshvorak          #+#    #+#             */
/*   Updated: 2018/06/15 20:26:45 by oshvorak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/corewar_vm.h"

void	op_aff(t_game *game, t_process *process)
{
	if (!check_codege(process->op_id, game->area[process->pc + 1].value))
		if (wrong_codage(game, process))
			return ;
	game->area[process->pc].pc = 0;
	if (check_reg_ind(game->area[process->pc + 2].value))
		ft_printf("%c\n",
		process->reg_num[game->area[process->pc + 2].value - 1] % 256);
	process->pc += 3;
	process->pc %= MEM_SIZE;
}
