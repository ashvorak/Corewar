/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_live.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oshvorak <oshvorak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/12 16:15:52 by oshvorak          #+#    #+#             */
/*   Updated: 2018/06/12 16:17:36 by oshvorak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/corewar_vm.h"

void	op_live(t_game *game, t_process *process)
{
	unsigned int	arg;

	process->live++;
	arg = write_4_bytes(game, process->PC);
	if (arg < 4 && game->players[arg].magic)
		game->players[arg].live = 1;
	game->area[process->PC].PC = 0;
	process->PC += 5;
}
