//
// Created by Dmytro LYTVYN on 6/5/18.
//


#include "../inc/corewar_vm.h"

void	op_st(t_game *game, t_process *process)
{
	unsigned int	arg2;
	int 			PC_jump;
	unsigned int    tmp;
	PC_jump = 3;
	
	if (!check_codege(process->op_id, game->area[process->PC + 1].value))
	{
		game->area[process->PC].PC = 0;
		process->PC++;
		process->op_id = 16;
		return ;
	}
	if (ret_arg(game->area[process->PC + 1].value, MASK_2, 4) == T_IND)
	{
		arg2 = write_2_bytes(game, process->PC + 3);
		PC_jump += 2;
		tmp = (process->PC + ((short)arg2 % IDX_MOD)) % MEM_SIZE;
		game->area[tmp].value = 0;
		game->area[tmp + 1].value = 0;
		game->area[tmp + 2].value = 0;
		game->area[tmp + 3].value = 0;
		game->area[tmp].value |= process->REG_NUM[game->area[process->PC + 2].value] >> 24;
		game->area[tmp + 1].value |= process->REG_NUM[game->area[process->PC + 2].value] >> 16;
		game->area[tmp + 2].value |= process->REG_NUM[game->area[process->PC + 2].value] >> 8;
		game->area[tmp + 3].value |= process->REG_NUM[game->area[process->PC + 2].value];
		game->area[tmp].color = process->color;
		game->area[tmp + 1].color = process->color;
		game->area[tmp + 2].color = process->color;
		game->area[tmp + 3].color = process->color;
		game->area[tmp].bold = 10;
		game->area[tmp + 1].bold = 10;
		game->area[tmp + 2].bold = 10;
		game->area[tmp + 3].bold = 10;
	}
	else if(ret_arg(game->area[process->PC + 1].value, MASK_2, 4) == T_REG)
	{
		process->REG_NUM[game->area[process->PC + 3].value - 1] = process->REG_NUM[game->area[process->PC + 2].value - 1];
		PC_jump += 1;
	}
	game->area[process->PC].PC = 0;
	process->PC += PC_jump;
}
