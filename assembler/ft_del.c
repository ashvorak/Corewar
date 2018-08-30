/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_del.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amazurok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/31 18:26:38 by amazurok          #+#    #+#             */
/*   Updated: 2018/06/04 13:09:54 by amazurok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "read.h"

char	*ft_del_comm(char *str)
{
	size_t	i;
	char	*tmp;

	i = 0;
	while (str[i] && str[i] != COMMENT_CHAR && str[i] != ';')
		i++;
	tmp = ft_strsub(str, 0, i);
	ft_strdel(&str);
	return (tmp);
}

void	ft_del_oper(t_oper *oper)
{
	t_oper *tmp;

	while (oper && oper->prev)
		oper = oper->prev;
	while (oper)
	{
		tmp = oper->next;
		ft_strdel(&oper->name);
		ft_strdel(&oper->arg1);
		ft_strdel(&oper->arg2);
		ft_strdel(&oper->arg3);
		free(oper);
		oper = tmp;
	}
}

void	ft_del_label(t_label *label)
{
	t_label *tmp;

	while (label && label->prev)
		label = label->prev;
	while (label)
	{
		tmp = label->next;
		ft_strdel(&label->name);
		ft_del_oper(label->oper);
		free(label);
		label = tmp;
	}
}

void	ft_del_data(t_read *data)
{
	ft_strdel(&data->file);
	ft_del_label(data->label);
	data->label = NULL;
	data->cm = 0;
	data->nm = 0;
	close(data->fd);
}
