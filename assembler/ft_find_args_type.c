/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_find_args_type.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aryabenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/30 10:49:36 by aryabenk          #+#    #+#             */
/*   Updated: 2018/06/09 16:40:10 by aryabenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_write.h"

ssize_t	ft_is_labellink(t_label *head, char *arg, t_label *label, t_bin *bin)
{
	int		bytelen;
	int		entry;
	ssize_t num;

	ft_set_val(&bytelen, &entry, 0, 0);
	while (head && ft_strcmp(label->name, head->name))
	{
		if (entry || (arg[0] == ':' ? !ft_strcmp(arg + 1, head->name) \
			: !ft_strcmp(arg + 2, head->name)))
		{
			bytelen += head->len;
			entry++;
		}
		head = head->next;
	}
	if ((head && !ft_strcmp(label->name, head->name) && entry) \
		|| (head && (arg[0] == ':' ? !ft_strcmp(arg + 1, head->name) \
			: !ft_strcmp(arg + 2, head->name))))
	{
		bytelen = bytelen == 0 ? bin->bytelen : bytelen + bin->bytelen;
		num = -bytelen;
	}
	else
		num = ft_find_len2link(label, arg[0] == ':' ? arg + 1 : arg + 2);
	return (num);
}

void	ft_ind_type(char *arg, t_bin *bin, t_label *label, t_label *head)
{
	ssize_t num;

	bin->size += 2;
	bin->res = realloc(bin->res, bin->size);
	if (arg[0] == ':')
		num = ft_is_labellink(head, arg, label, bin);
	else
		num = ft_atoi(arg);
	ft_add_2_bytenum(num, bin);
}

void	ft_dir_type(char *arg, t_bin *bin, t_label *label, t_label *head)
{
	ssize_t num;

	bin->size += g_op_tab[bin->j].label_size;
	bin->res = realloc(bin->res, bin->size);
	if (arg[1] == ':')
		num = ft_is_labellink(head, arg, label, bin);
	else
		num = ft_atoi(arg + 1);
	if (g_op_tab[bin->j].label_size == 2)
		ft_add_2_bytenum(num, bin);
	else if (g_op_tab[bin->j].label_size == 4)
		ft_add_4_bytenum(num, bin);
}

void	ft_reg_type(char *arg, t_bin *bin)
{
	ssize_t num;

	bin->size += 1;
	bin->res = realloc(bin->res, bin->size);
	num = ft_atoi(arg);
	bin->res[bin->i] = (t_uchar)(num);
	bin->i++;
}

void	ft_find_arg_type(t_label *label, t_bin *bin, t_label *head)
{
	char	*arg;
	int		count;

	count = 1;
	while (count < 4)
	{
		if (count == 1)
			arg = label->oper->arg1;
		else if (count == 2)
			arg = label->oper->arg2;
		else
			arg = label->oper->arg3;
		if (arg && arg[0] == 'r')
			ft_reg_type(arg + 1, bin);
		else if (arg && arg[0] == '%')
			ft_dir_type(arg, bin, label, head);
		else if (arg && (ft_isdigit(arg[0]) || arg[0] == ':' || arg[0] == '-'))
			ft_ind_type(arg, bin, label, head);
		count++;
	}
}
