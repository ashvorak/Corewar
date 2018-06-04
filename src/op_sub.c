//
// Created by Dmytro LYTVYN on 6/3/18.
//

#include "../inc/corewar_vm.h"

void    op_sub(t_game *game, t_process *process)
{
	unsigned int res;

	res = 0;
	if (!check_codege(process->op_id, ft_atoi_base(game->area[process->PC + 1].value, 16)))
		return ;
	res = game->area[process->PC + 2].value - game->area[process->PC + 3].value;
	ft_strdel(&game->area[process->PC + 4].value);
	game->area[process->PC + 4].value = res;
	if (res == 0)
		process->carry = 1;
	else
		process->carry = 0;
}