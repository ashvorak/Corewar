/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_process.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlytvyn <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/16 10:48:50 by dlytvyn           #+#    #+#             */
/*   Updated: 2018/06/16 10:48:51 by dlytvyn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/corewar_vm.h"

int				processes_number(t_game *game)
{
	int			i;
	t_process	*tmp;

	i = 0;
	tmp = game->process;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}

static void		execute_process_add(t_game *game, t_process *process)
{
	if (process->op_id == 10)
		op_sti(game, process);
	else if (process->op_id == 11)
		op_fork(game, process);
	else if (process->op_id == 12)
		op_lld(game, process);
	else if (process->op_id == 13)
		op_lldi(game, process);
	else if (process->op_id == 14)
		op_lfork(game, process);
	else if (process->op_id == 15)
		op_aff(game, process);
}

void			execute_process(t_game *game, t_process *process)
{
	if (process->op_id == 0)
		op_live(game, process);
	else if (process->op_id == 1)
		op_ld(game, process);
	else if (process->op_id == 2)
		op_st(game, process);
	else if (process->op_id == 3)
		op_add(game, process);
	else if (process->op_id == 4)
		op_sub(game, process);
	else if (process->op_id == 5)
		op_and(game, process);
	else if (process->op_id == 6)
		op_or(game, process);
	else if (process->op_id == 7)
		op_xor(game, process);
	else if (process->op_id == 8)
		op_zjmp(game, process);
	else if (process->op_id == 9)
		op_ldi(game, process);
	else
		execute_process_add(game, process);
}
