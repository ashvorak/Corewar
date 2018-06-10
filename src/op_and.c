//
// Created by Dmytro LYTVYN on 6/3/18.
//

#include "../inc/corewar_vm.h"

unsigned int     write_arg(t_process *process, t_game *game, int tt, int PC)
{
	unsigned int tmp;
	
	if (tt == T_DIR)
		return(write_4_bytes(game, PC));
	else if (tt == T_IND)
	{
		tmp = write_2_bytes(game, PC);
		return (write_4_bytes(game, PC + (short)tmp));
	}
	else
	{
		tmp = game->area[PC].value;
		return (process->REG_NUM[(unsigned char)tmp - 1]);
	}
}

int     plus_PC(int codage, int MASK, int move)
{
	if (ret_arg(codage, MASK, move) == T_REG)
		return (1);
	else if (ret_arg(codage, MASK, move) == T_DIR)
		return (4);
	else
		return (2);
}

void    op_and(t_game *game, t_process *process)
{
	int             PC_buf;
	unsigned int    arg1;
	unsigned int    arg2;
	unsigned int    arg3;
	
	if (!check_codege(process->op_id, game->area[process->PC + 1].value))
	{
		game->area[process->PC].PC = 0;
		process->PC += 2;
		process->op_id = 16;
		return ;
	}
	PC_buf = 2;
	arg1 = write_arg(process, game, ret_arg(game->area[process->PC + 1].value, MASK_1, 6), process->PC + PC_buf);
	PC_buf += plus_PC(game->area[process->PC + 1].value, MASK_1, 6);
	arg2 = write_arg(process, game, ret_arg(game->area[process->PC + 1].value, MASK_2, 4), process->PC + PC_buf);
	PC_buf += plus_PC(game->area[process->PC + 1].value, MASK_2, 4);
	arg3 = game->area[process->PC + PC_buf].value;
	PC_buf += 1;
	process->REG_NUM[arg3 - 1] = arg1 & arg2;
	if (process->REG_NUM[arg3 - 1] == 0)
		process->carry = 1;
	else
		process->carry = 0;
	game->area[process->PC].PC = 0;
	process->PC += PC_buf;
}
