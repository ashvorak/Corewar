//
// Created by Dmytro LYTVYN on 6/3/18.
//

#include "../inc/corewar_vm.h"

static int write_arg(unsigned int *arg, t_game *game, int tt, int PC)
{
	if (tt == T_DIR)
	{
		*arg = write_4_bytes(game, PC + 2);
		return (4);
	}
	else if (tt == T_IND)
	{
		*arg = write_2_bytes(game, PC + 2);
		return (2);
	}
	else
	{
		*arg = game->area[PC + 2].value;
		return (1);
	}
}

void    op_and(t_game *game, t_process *process)
{
	int             PC_buf;
	unsigned int    arg1;
	unsigned int    arg2;
	unsigned int    arg3;
	
	if (!check_codege(process->op_id, game->area[process->PC + 1].value))
		return ;
	PC_buf = 1;
	PC_buf += write_arg(&arg1, game, ret_arg(game->area[process->PC + 1].value, MASK_1, 6), process->PC);
	PC_buf += write_arg(&arg2, game, ret_arg(game->area[process->PC + 1].value, MASK_2, 4), PC_buf);
	arg3 = game->area[PC_buf + 2].value;
	PC_buf += 2;
	process->REG_NUM[arg3] = arg1 & arg2;
	if (process->REG_NUM[arg3] == 0)
		process->carry = 1;
	else
		process->carry = 0;
	game->area[process->PC].PC = 0;
	process->PC += PC_buf;
}
