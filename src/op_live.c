#include "../inc/corewar_vm.h"

void    op_live(t_game *game, t_process *process)
{
	int 	arg;

	process->live++;
	arg = write_4_bytes(game, process->PC);
	if (arg >= 0 && arg < 4 && game->players[arg].magic)
		game->players[arg].live = 1;
	process->PC += 5;
}