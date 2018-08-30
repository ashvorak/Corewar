/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_valid.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amazurok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/31 18:17:01 by amazurok          #+#    #+#             */
/*   Updated: 2018/06/07 14:32:44 by amazurok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "read.h"

int		ft_t_check(int a, int b)
{
	if (a == T_REG)
		return ((b == T_REG) || (b == (T_REG | T_DIR)) || \
		(b == (T_REG | T_IND)) || (b == (T_REG | T_DIR | T_IND)));
	else if (a == T_DIR)
		return ((b == T_DIR) || (b == (T_DIR | T_REG)) || \
		(b == (T_DIR | T_IND)) || (b == (T_REG | T_DIR | T_IND)));
	else if (a == T_IND)
		return ((b == T_IND) || (b == (T_IND | T_REG)) || \
		(b == (T_IND | T_DIR)) || (b == (T_REG | T_DIR | T_IND)));
	else
		return (0);
}

int		ft_isnumber(char *num)
{
	int i;

	i = 0;
	i += num[i] == '-' ? 1 : 0;
	if (!num[i])
		return (0);
	while (num[i])
	{
		if (!ft_isdigit(num[i]))
			return (0);
		i++;
	}
	return (1);
}

int		ft_valid_label(char *lable, int k)
{
	int i;

	i = k;
	if (k && lable && lable[0] != ':')
		return (0);
	while (lable && lable[i])
	{
		if (!ft_srchinstr(LABEL_CHARS, lable[i]))
			return (0);
		i++;
	}
	return (lable ? 1 : 0);
}

int		ft_valid_opname(char *name)
{
	if (ft_src_name(name) < 0)
		return (0);
	return (1);
}

int		ft_valid_arg(t_read *data, char *arg, t_op op, int arg_n)
{
	int t;

	t = ft_atoi(arg + 1);
	t = t < 1 ? REG_NUMBER + 1 : t;
	if (arg && arg[0] == 'r')
	{
		ft_isnumber(arg + 1) && t <= REG_NUMBER ? 0 : \
			ft_error(data, "Doesn`t valid rx", arg, NULL);
		return (ft_t_check(T_REG, op.type[arg_n]) || \
				ft_t_check(T_IND, op.type[arg_n]) ? 1 : 0);
	}
	else if (arg && arg[0] == DIRECT_CHAR)
	{
		if (ft_t_check(T_DIR, op.type[arg_n]))
			return (ft_isnumber(arg + 1) ? 1 : ft_valid_label(arg + 1, 1));
		return (0);
	}
	else if (arg && (arg[0] == ':' || ft_isdigit(arg[0]) || arg[0] == '-'))
	{
		if (ft_t_check(T_IND, op.type[arg_n]))
			return (ft_isnumber(arg) ? 1 : ft_valid_label(arg, 1));
		return (0);
	}
	return (0);
}
