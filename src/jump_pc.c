/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jump_pc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oshvorak <oshvorak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/09 18:12:18 by oshvorak          #+#    #+#             */
/*   Updated: 2018/06/12 15:21:59 by oshvorak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/corewar_vm.h"

int		ret_jump(unsigned char codage, int mask, int move, int op_id)
{
	int a;

	if (move == 6)
		a = 0;
	else if (move == 4)
		a = 1;
	else
		a = 2;
	if (ret_arg(codage, mask, move) == T_DIR && g_op_tab[op_id].arg_type[a])
	{
		if (g_op_tab[op_id].label == 4)
			return (4);
		else
			return (2);
	}
	else if (ret_arg(codage, mask, move) == T_IND && g_op_tab[op_id].arg_type[a])
		return (2);
	else if (ret_arg(codage, mask, move) == T_REG && g_op_tab[op_id].arg_type[a])
		return (1);
	else
		return (0);
}

int		jump_pc(unsigned char codage, int op_id)
{
	int pc_jump;

	pc_jump = 2;
	pc_jump += ret_jump(codage, MASK_1, 6, op_id);
	pc_jump += ret_jump(codage, MASK_2, 4, op_id);
	pc_jump += ret_jump(codage, MASK_3, 2, op_id);
	pc_jump %= MEM_SIZE;
	return (pc_jump);
}
