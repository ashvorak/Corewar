/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_zjmp.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oshvorak <oshvorak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/02 12:47:38 by oshvorak          #+#    #+#             */
/*   Updated: 2018/06/04 11:06:33 by oshvorak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/corewar_vm.h"

void	op_zjmp(t_game *game, t_process *process)
{
	unsigned int 	res;

	if (game->process->carry)
	{
		res = write_2_bytes(game, process->PC + 1);
		game->area[process->PC].PC = 0;
		process->PC += res;
		if (process->PC > 4095)
			process->PC %= 4096;
	}
	else
	{
		game->area[process->PC].PC = 0;
		process->PC++;
	}
}
