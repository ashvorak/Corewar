/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_opcode.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aryabenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/29 13:47:14 by aryabenk          #+#    #+#             */
/*   Updated: 2018/06/07 13:34:28 by aryabenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_write.h"

t_uchar	ft_return_codage(t_oper *oper)
{
	t_uchar codage;

	codage = 0;
	if (oper->arg1 && oper->arg1[0] == 'r')
		codage = codage | (t_uchar)(REG_CODE << 6);
	else if (oper->arg1 && oper->arg1[0] == '%')
		codage = codage | (t_uchar)(DIR_CODE << 6);
	else if (oper->arg1 && (ft_isdigit(oper->arg1[0]) || oper->arg1[0] == '-' \
		|| oper->arg1[0] == ':'))
		codage = codage | (t_uchar)(IND_CODE << 6);
	if (oper->arg2 && oper->arg2[0] == 'r')
		codage = codage | (t_uchar)(REG_CODE << 4);
	else if (oper->arg2 && oper->arg2[0] == '%')
		codage = codage | (t_uchar)(DIR_CODE << 4);
	else if (oper->arg2 && (ft_isdigit(oper->arg2[0]) || oper->arg2[0] == '-' \
		|| oper->arg2[0] == ':'))
		codage = codage | (t_uchar)(IND_CODE << 4);
	if (oper->arg3 && oper->arg3[0] == 'r')
		codage = codage | (t_uchar)(REG_CODE << 2);
	else if (oper->arg3 && oper->arg3[0] == '%')
		codage = codage | (t_uchar)(DIR_CODE << 2);
	else if (oper->arg3 && (ft_isdigit(oper->arg3[0]) || oper->arg3[0] == '-' \
		|| oper->arg3[0] == ':'))
		codage = codage | (t_uchar)(IND_CODE << 2);
	return (codage);
}

ssize_t	ft_return_oper_ind(char *name)
{
	ssize_t i;

	i = 0;
	while (ft_strcmp(g_op_tab[i].name, name))
		i++;
	return (i);
}

void	ft_add_operation(t_bin *bin, t_label *label, t_label *head)
{
	t_uchar	codage;

	bin->opr++;
	bin->res = realloc(bin->res, ++bin->size);
	bin->j = ft_return_oper_ind(label->oper->name);
	bin->res[bin->i++] = (t_uchar)(g_op_tab[bin->j].code);
	codage = ft_return_codage(label->oper);
	if (g_op_tab[bin->j].codage)
	{
		bin->res = realloc(bin->res, ++bin->size);
		bin->res[bin->i++] = (t_uchar)codage;
	}
	ft_find_arg_type(label, bin, head);
	bin->bytelen = bin->size - bin->oldsize;
}

void	ft_add_opcode(t_bin *bin, t_label *label)
{
	t_label	*head;
	t_oper	*node;

	bin->i = bin->size;
	head = label;
	while (label)
	{
		bin->oldsize = bin->size;
		bin->bytelen = 0;
		bin->opr = 0;
		node = label->oper;
		while (label->oper)
		{
			ft_add_operation(bin, label, head);
			label->oper = label->oper->next;
		}
		label->oper = node;
		label->len += (size_t)bin->size - bin->oldsize;
		label = label->next;
	}
}
