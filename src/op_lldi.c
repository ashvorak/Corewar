/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_lldi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oshvorak <oshvorak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/07 11:52:06 by oshvorak          #+#    #+#             */
/*   Updated: 2018/06/14 12:33:15 by oshvorak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/corewar_vm.h"

<<<<<<< HEAD
static int	ret_arg1(t_game *game, t_process *process, unsigned int codage)
{
	unsigned int	arg1;
	unsigned int	t_ind;

	if (ret_arg(codage, MASK_1, 6) == T_DIR)
	{
		arg1 = write_2_bytes(game, process->pc + 2);
		arg1 = (short)arg1;
		process->pc += 4;
=======
static unsigned int	ret_arg1(t_game *game, t_process *process, unsigned int codage)
{
	unsigned int	arg1;
	unsigned int	t_ind;
	
	if (ret_arg(codage, MASK_1, 6) == T_DIR)
	{
		arg1 = write_2_bytes(game, (process->pc + 2) % MEM_SIZE);
		arg1 = (short)arg1;
		process->pc = (process->pc + 4) % MEM_SIZE;
>>>>>>> bd5b5d765e70032b433c52be6aac2f9fb3ffdf7f
	}
	else if (ret_arg(game->area[(process->pc + 1) % MEM_SIZE].value, MASK_1, 6) == T_IND)
	{
		t_ind = (short)write_2_bytes(game, (process->pc + 2) % MEM_SIZE);
		arg1 = write_4_bytes(game, ((t_ind % IDX_MOD) + process->pc) % MEM_SIZE);
<<<<<<< HEAD
		process->pc += 4;
	}
	else
	{
		arg1 = process->reg_num[game->area[process->pc + 2].value - 1];
		process->pc += 3;
=======
		process->pc = (process->pc + 4) % MEM_SIZE;
	}
	else
	{
		arg1 = process->reg_num[game->area[(process->pc + 2) % MEM_SIZE].value - 1];
		process->pc = (process->pc + 3) % MEM_SIZE;
>>>>>>> bd5b5d765e70032b433c52be6aac2f9fb3ffdf7f
	}
	return (arg1);
}

<<<<<<< HEAD
static int	ret_arg2(t_game *game, t_process *process, unsigned int codage)
{
	unsigned int	arg2;

=======
static unsigned int	ret_arg2(t_game *game, t_process *process, unsigned int codage)
{
	unsigned int	arg2;
	
>>>>>>> bd5b5d765e70032b433c52be6aac2f9fb3ffdf7f
	if (ret_arg(codage, MASK_2, 4) == T_DIR)
	{
		arg2 = write_2_bytes(game, process->pc);
		arg2 = (short)arg2;
<<<<<<< HEAD
		process->pc += 2;
=======
		process->pc = (process->pc + 2) % MEM_SIZE;
>>>>>>> bd5b5d765e70032b433c52be6aac2f9fb3ffdf7f
	}
	else
	{
		arg2 = process->reg_num[game->area[process->pc].value - 1];
<<<<<<< HEAD
		process->pc += 1;
=======
		process->pc = (process->pc + 1) % MEM_SIZE;
>>>>>>> bd5b5d765e70032b433c52be6aac2f9fb3ffdf7f
	}
	return (arg2);
}

void		op_ldi(t_game *game, t_process *process)
{
	unsigned int	arg1;
	unsigned int	arg2;
	unsigned int	arg3;
	unsigned int	codage;
	int				pc_buf;
	
	if (!check_codege(process->op_id, game->area[process->pc + 1].value))
	{
		game->area[process->pc].pc = 0;
<<<<<<< HEAD
		process->pc += jump_pc(game->area[process->pc + 1].value, \
		process->op_id);
=======
		process->pc += jump_pc(game->area[(process->pc + 1) % MEM_SIZE].value, \
		process->op_id);
		process->pc %= MEM_SIZE;
>>>>>>> bd5b5d765e70032b433c52be6aac2f9fb3ffdf7f
		process->op_id = 16;
		return ;
	}
	pc_buf = process->pc;
<<<<<<< HEAD
	codage = game->area[process->pc + 1].value;
=======
	codage = game->area[(process->pc + 1) % MEM_SIZE].value;
>>>>>>> bd5b5d765e70032b433c52be6aac2f9fb3ffdf7f
	game->area[process->pc].pc = 0;
	arg1 = ret_arg1(game, process, codage);
	arg2 = ret_arg2(game, process, codage);
	arg3 = game->area[process->pc++].value;
<<<<<<< HEAD
	//ft_printf("index %d\n", mod(((((int)arg1 + (int)arg2) % IDX_MOD) % MEM_SIZE + pc_buf) % MEM_SIZE));
	process->reg_num[arg3 - 1] = write_4_bytes(game, ((((int)arg1 + (int)arg2)) + pc_buf) % MEM_SIZE);
	process->carry = process->reg_num[arg3 - 1] == 0 ? 1 : 0;
=======
	process->pc %= MEM_SIZE;
	process->reg_num[arg3 - 1] = write_4_bytes(game, (((int)arg1 \
	+ (int)arg2) + pc_buf) % MEM_SIZE);
	process->carry = (process->reg_num[arg3 - 1] == 0) ? 1 : 0;
}
>>>>>>> bd5b5d765e70032b433c52be6aac2f9fb3ffdf7f
