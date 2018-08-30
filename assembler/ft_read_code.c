/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_code.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amazurok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/02 12:16:07 by amazurok          #+#    #+#             */
/*   Updated: 2018/06/07 11:56:37 by amazurok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "read.h"

int		ft_find_lbname(t_label *lst, char *name)
{
	while (lst)
	{
		if (ft_strequ(lst->name, name))
			return (1);
		lst = lst->next;
	}
	return (0);
}

void	ft_check_label(t_read *data, t_label *lst)
{
	t_oper	*heado;
	t_label	*headl;

	data->label = ft_gotoheadlb(lst);
	lst = data->label;
	headl = lst;
	while (lst)
	{
		heado = lst->oper;
		while (lst->oper)
		{
			if (lst->oper->arg1 && ft_strstr(lst->oper->arg1, "%:"))
				ft_find_lbname(headl, lst->oper->arg1 + 2) ? 0 : \
					ft_error(data, "No such label", NULL, NULL);
			if (lst->oper->arg2 && ft_strstr(lst->oper->arg2, "%:"))
				ft_find_lbname(headl, lst->oper->arg2 + 2) ? 0 : \
					ft_error(data, "No such label", NULL, NULL);
			if (lst->oper->arg3 && ft_strstr(lst->oper->arg3, "%:"))
				ft_find_lbname(headl, lst->oper->arg3 + 2) ? 0 : \
					ft_error(data, "No such label", NULL, NULL);
			lst->oper = lst->oper->next;
		}
		lst->oper = heado;
		lst = lst->next;
	}
}

void	ft_read_code(t_read *data)
{
	int		i;
	char	*str;
	char	*trim;

	get_next_line(data->fd, &str);
	str = ft_del_comm(str);
	trim = ft_strtrim(str);
	trim && trim[0] ? ft_error(data, "Syntax error", str, trim) : 0;
	ft_strdel(&str);
	ft_strdel(&trim);
	while (get_next_line(data->fd, &str))
	{
		i = 0;
		str = ft_del_comm(str);
		trim = ft_strtrim(str);
		if (ft_chardospace(trim, LABEL_CHAR))
			ft_read_label(data, trim, &i);
		if (trim[i])
			ft_read_arg_lb(data, trim, &i);
		ft_strdel(&str);
		ft_strdel(&trim);
	}
	data->label ? data->label->oper = ft_gotoheadop(data->label->oper) : \
		ft_error(data, "No code", str, trim);
	ft_check_label(data, data->label);
}
