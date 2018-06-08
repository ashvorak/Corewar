#include "../inc/corewar_vm.h"

unsigned int write_2_bytes(t_game *game, int PC)
{
	unsigned int arg;

	arg = game->area[PC].value << 8;
	arg = arg | game->area[PC + 1].value;
	return (arg);
}

unsigned int write_4_bytes(t_game *game, int PC)
{
	unsigned int arg;

	arg = game->area[PC].value << 24;
	arg = arg | (game->area[PC + 1].value << 16);
	arg = arg | (game->area[PC + 2].value << 8);
	arg = arg | game->area[PC + 3].value;
	return (arg);
}
