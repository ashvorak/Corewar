/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_addit_func.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amazurok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/29 16:29:50 by amazurok          #+#    #+#             */
/*   Updated: 2018/06/07 17:05:21 by amazurok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "read.h"

void		ft_error(t_read *data, char *msg, void *b, void *c)
{
	errno = 5;
	perror(msg);
	ft_del_data(data);
	b ? free(b) : 0;
	c ? free(c) : 0;
	exit(1);
}

int			ft_space(char c)
{
	return (c == ' ' || c == '\t' || c == '\n');
}

int			ft_skip_space(char *file, int i)
{
	while (file && file[i] && ft_space(file[i]))
		i++;
	return (i);
}

int			ft_chardospace(char *str, char c)
{
	int i;

	i = ft_skip_space(str, 0);
	while (str[i] && !ft_space(str[i]))
	{
		if (str[i] == DIRECT_CHAR)
			return (0);
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

int			ft_src_name(char *name)
{
	int i;

	i = 0;
	while (g_op_tab[i].name)
	{
		if (ft_strequ(g_op_tab[i].name, name))
			return (i);
		i++;
	}
	return (-1);
}
