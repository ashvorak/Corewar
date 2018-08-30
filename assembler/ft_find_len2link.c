/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_find_len2link.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aryabenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/31 14:52:18 by aryabenk          #+#    #+#             */
/*   Updated: 2018/05/31 18:20:59 by aryabenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_write.h"

ssize_t	ft_find_args_size(char *arg, int j)
{
	int size;

	size = 0;
	if (arg && arg[0] == 'r')
		size = 1;
	else if (arg && arg[0] == '%')
		size = g_op_tab[j].label_size;
	else if (arg && (ft_isdigit(arg[0]) || arg[0] == ':' || arg[0] == '-'))
		size = 2;
	return (size);
}

ssize_t	ft_find_len2link(t_label *label, char *arg)
{
	ssize_t	size;
	int		j;
	t_oper	*head;

	size = 0;
	while (label && ft_strcmp(arg, label->name))
	{
		head = label->oper;
		while (label->oper)
		{
			size++;
			j = ft_return_oper_ind(label->oper->name);
			size += g_op_tab[j].codage ? 1 : 0;
			size += ft_find_args_size(label->oper->arg1, j);
			size += ft_find_args_size(label->oper->arg2, j);
			size += ft_find_args_size(label->oper->arg3, j);
			label->oper = label->oper->next;
		}
		label->oper = head;
		label = label->next;
	}
	return (size);
}
