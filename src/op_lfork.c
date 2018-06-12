/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_lfork.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oshvorak <oshvorak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/12 16:15:16 by oshvorak          #+#    #+#             */
/*   Updated: 2018/06/12 16:15:43 by oshvorak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/corewar_vm.h"

void	op_lfork(t_game *game, t_process *process)
{
	unsigned int arg;

	arg = write_2_bytes(game, (process->PC + 1) % MEM_SIZE);
	game->area[process->PC].PC = 0;
	clone_process(game, process, (process->PC + ((short)arg)) % MEM_SIZE);
	process->PC += 3;
}
