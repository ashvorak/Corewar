/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jump_pc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oshvorak <oshvorak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/09 18:12:18 by oshvorak          #+#    #+#             */
/*   Updated: 2018/06/11 14:02:36 by oshvorak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/corewar_vm.h"

int		ret_jump(unsigned char codage, int mask, int move, int op_id, int arg)
{
	if (ret_arg(codage, mask, move) == T_DIR && op_tab[op_id].arg_type[arg])
	{
		if (op_tab[op_id].label == 4)
			return (4);
		else
			return (2);
	}
	else if (ret_arg(codage, mask, move) == T_IND && op_tab[op_id].arg_type[arg])
		return (2);
	else if (ret_arg(codage, mask, move) == T_REG && op_tab[op_id].arg_type[arg])
		return (1);
	else
		return (0);
}

int		jump_pc(unsigned char codage, int op_id)
{
	int PC_jump;

	PC_jump = 2;
	PC_jump += ret_jump(codage, MASK_1, 6, op_id, 0);
	PC_jump += ret_jump(codage, MASK_2, 4, op_id, 1);
	PC_jump += ret_jump(codage, MASK_3, 2, op_id, 2);
	return (PC_jump);
}