//
// Created by Dmytro LYTVYN on 6/7/18.
//

#include "../inc/corewar_vm.h"

static  t_process   *copy_reg(t_process *clone, t_process *process)
{
	int i;
	
	i = 0;
	while (i < 16)
	{
		clone->REG_NUM[i] = process->REG_NUM[i];
		i++;
	}
	return (clone);
}

void                clone_process(t_game *game, t_process *process, int location)
{
	t_process *tmp;
	t_process *clone;
	
	if (!(clone = (t_process*)malloc(sizeof(t_process))))
		exit(1);
	ft_bzero(clone->REG_NUM, 16);
	clone = copy_reg(clone, process);
	clone->PC = location;
	clone->live = process->live;
	clone->op_id = push_op_id(game->area[clone->PC].value);
	clone->CYCLE_TO_DONE = 0;
	clone->carry = process->carry;
	clone->num = number++;
	clone->next = NULL;
	clone->prev = NULL;
	if (game->process)
	{
		tmp = game->process;
		clone->next = tmp;
		tmp->prev = clone;
		game->process = clone;
	}
	else
		game->process = clone;
}

void                op_fork(t_game *game, t_process *process)
{
	int arg;
	
	arg = write_2_bytes(game, process->PC + 1);
	game->area[process->PC].PC = 0;
	clone_process(game, process, (arg % IDX_MOD) + process->PC);
	process->PC += 3;
	//game->area[game->process->PC].PC = 1;
}
