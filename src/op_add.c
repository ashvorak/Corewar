//
// Created by Dmytro LYTVYN on 6/3/18.
//

#include "../inc/corewar_vm.h"

void    op_add(t_game *game, t_process *process)
{
	if (!check_codege(process->op_id, game->area[process->PC + 1].value))
	{
		game->area[process->PC].PC = 0;
		process->PC++;
		process->op_id = 16;
		return ;
	}
	game->process->REG_NUM[process->PC + 4] = process->REG_NUM[game->area[process->PC
		+ 2].value] & process->REG_NUM[game->area[process->PC + 3].value];
	game->area[process->PC].PC = 0;
	process->PC += 5;
	if (game->process->REG_NUM[process->PC + 4] == 0)
		process->carry = 1;
	else
		process->carry = 0;
}