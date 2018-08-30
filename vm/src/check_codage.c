/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_codage.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oshvorak <oshvorak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/02 13:08:41 by oshvorak          #+#    #+#             */
/*   Updated: 2018/06/02 15:20:39 by oshvorak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/corewar_vm.h"

int		check_arg(int arg, int op_id, int arg_num)
{
	if (arg == T_REG)
	{
		if ((arg == g_op_tab[op_id].arg_type[arg_num]) || ((arg | T_DIR) ==
			g_op_tab[op_id].arg_type[arg_num]) \
			|| ((arg | T_IND) == g_op_tab[op_id].arg_type[arg_num]) ||
			((arg | T_DIR | T_IND) == g_op_tab[op_id].arg_type[arg_num]))
			return (1);
	}
	else if (arg == T_DIR)
	{
		if ((arg == g_op_tab[op_id].arg_type[arg_num]) || ((arg | T_REG) ==
			g_op_tab[op_id].arg_type[arg_num]) \
			|| ((arg | T_IND) == g_op_tab[op_id].arg_type[arg_num]) ||
			((arg | T_REG | T_IND) == g_op_tab[op_id].arg_type[arg_num]))
			return (1);
	}
	else if (arg == T_IND)
	{
		if ((arg == g_op_tab[op_id].arg_type[arg_num]) || ((arg | T_DIR) ==
			g_op_tab[op_id].arg_type[arg_num]) \
			|| ((arg | T_REG) == g_op_tab[op_id].arg_type[arg_num]) ||
			((arg | T_DIR | T_REG) == g_op_tab[op_id].arg_type[arg_num]))
			return (1);
	}
	return (0);
}

int		ret_arg(int codage, int mask, int move)
{
	int arg;

	arg = 0;
	if (((codage & mask) >> move) == T_REG)
		arg = T_REG;
	else if (((codage & mask) >> move) == T_DIR)
		arg = T_DIR;
	else if (((codage & mask) >> move) == T_IND)
		arg = T_IND;
	return (arg);
}

int		check_codege(int op_id, int codage)
{
	int arg1;
	int arg2;
	int arg3;

	arg1 = ret_arg(codage, MASK_1, 6);
	if (!check_arg(arg1, op_id, 0))
		return (0);
	arg2 = ret_arg(codage, MASK_2, 4);
	if (arg2)
	{
		if (!check_arg(arg2, op_id, 1))
			return (0);
		arg3 = ret_arg(codage, MASK_3, 2);
		if (arg3 && !check_arg(arg3, op_id, 2))
			return (0);
	}
	return (1);
}
