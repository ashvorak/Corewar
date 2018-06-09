#include "../inc/corewar_vm.h"

void    op_live(t_game *game, t_process *process)
{
	unsigned int 	arg;

	process->live++;
	arg = write_4_bytes(game, process->PC);
	if (arg < 4 && game->players[arg].magic)
		game->players[arg].live = 1;
	game->area[process->PC].PC = 0;
	process->PC += 5;
}