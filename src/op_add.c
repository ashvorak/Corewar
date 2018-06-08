//
// Created by Dmytro LYTVYN on 6/3/18.
//

#include "../inc/corewar_vm.h"

void    op_add(t_game *game, t_process *process)
{
	if (!check_codege(process->op_id,
	    ft_atoi_base(game->area[process->PC + 1].value, 16)))
		return ;
	game->process->REG_NUM[process->PC + 3] = process->REG_NUM[game->area[process->PC
		+ 1].value] | process->REG_NUM[game->area[process->PC + 3].value - 1];
	if (game->process->REG_NUM[process->PC + 3] == 0)
		process->carry = 1;
	else
		process->carry = 0;
}
