//
// Created by Dmytro LYTVYN on 6/7/18.
//

#include "../inc/corewar_vm.h"

void                op_lfork(t_game *game, t_process *process)
{
	unsigned int arg;
	
	arg = write_2_bytes(game, (process->PC + 1) % MEM_SIZE);
	game->area[process->PC].PC = 0;
	clone_process(game, process, (process->PC + ((short)arg)) % MEM_SIZE);
	process->PC += 3;
}