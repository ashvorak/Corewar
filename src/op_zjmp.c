/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_zjmp.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oshvorak <oshvorak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/02 12:47:38 by oshvorak          #+#    #+#             */
/*   Updated: 2018/06/02 15:10:06 by oshvorak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/corewar_vm.h"

void	op_zjmp(t_game *game, t_process *process)
{
	int 	res;
	char	*tmp;

	if (game->process->carry)
	{
		tmp = ft_strjoin(game->area[process->PC + 1].value, game->area[process->PC + 2].value);
		res = ft_atoi_base(tmp, 16);
		process->PC = res / IDX_MOD;
	}
}


