/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_zjmp.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oshvorak <oshvorak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/02 12:47:38 by oshvorak          #+#    #+#             */
/*   Updated: 2018/06/13 14:37:02 by oshvorak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/corewar_vm.h"

void	op_zjmp(t_game *game, t_process *process)
{
	unsigned int	res;

	if (process->carry)
	{
		res = write_2_bytes(game, process->pc + 1);
		game->area[process->pc].pc = 0;
		process->pc += (((short)res) % IDX_MOD);
	}
	else
	{
		game->area[process->pc].pc = 0;
		process->pc += 3;
	}
	process->pc %= MEM_SIZE;
}
