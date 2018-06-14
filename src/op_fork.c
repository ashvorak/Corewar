/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_fork.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oshvorak <oshvorak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/12 16:01:28 by oshvorak          #+#    #+#             */
/*   Updated: 2018/06/12 16:05:34 by oshvorak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/corewar_vm.h"

static t_process	*copy_reg(t_process *clone, t_process *process)
{
	int i;

	i = 0;
	while (i < 16)
	{
		clone->reg_num[i] = process->reg_num[i];
		i++;
	}
	return (clone);
}



void				clone_process(t_game *game, t_process *p, int pc)
{
	t_process *tmp;
	t_process *clone;

	if (!(clone = (t_process*)malloc(sizeof(t_process))))
		exit(1);
	ft_bzero(clone->reg_num, 16);
	clone = copy_reg(clone, p);
	pc = mod(pc);
	clone->pc = (unsigned int)pc;
	clone->live = p->live;
	clone->op_id = push_op_id(game->area[clone->pc].value);
	clone->cycle_to_done = 0;
	clone->carry = p->carry;
	clone->color = p->color;
	clone->num = g_number++;
	clone->next = NULL;
	if (game->process)
	{
		tmp = game->process;
		clone->next = tmp;
		game->process = clone;
	}
	else
		game->process = clone;
}

void				op_fork(t_game *game, t_process *process)
{
	int arg;
	
	arg = (short)write_2_bytes(game, (process->pc + 1) % MEM_SIZE);
	game->area[process->pc].pc = 0;
	clone_process(game, process, (process->pc + (arg % IDX_MOD)) % MEM_SIZE);
	process->pc = (process->pc + 3) % MEM_SIZE;
}
