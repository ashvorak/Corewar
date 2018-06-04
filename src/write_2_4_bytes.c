#include "../inc/corewar_vm.h"

unsigned int write_2_bytes(t_game *game, int PC, int diff)
{
	unsigned int arg;

	arg = game->area[PC + diff].value << 8;
	arg = arg | game->area[PC + diff + 1].value;
	return (arg);
}

unsigned int write_4_bytes(t_game *game, int PC, int diff)
{
	unsigned int arg;

	arg = game->area[PC + diff].value << 24;
	arg = arg | (game->area[PC + diff + 1].value << 16);
	arg = arg | (game->area[PC + diff + 2].value << 8);
	arg = arg | game->area[PC + diff + 3].value;
	return (arg);
}