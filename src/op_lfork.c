//
// Created by Dmytro LYTVYN on 6/7/18.
//

#include "../inc/corewar_vm.h"

void                op_lfork(t_game *game, t_process *process)
{
	int arg;
	
	arg = write_2_bytes(game, process->PC + 1);
	clone_process(game, process, arg);
}