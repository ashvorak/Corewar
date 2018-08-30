/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_label.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amazurok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/02 12:23:47 by amazurok          #+#    #+#             */
/*   Updated: 2018/06/07 14:18:30 by amazurok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "read.h"

char	*ft_readopername(char *file, int *i)
{
	int		j;
	char	*res;

	*i = ft_skip_space(file, *i);
	j = *i;
	while (file[j] && !ft_space(file[j]) && file[j] != DIRECT_CHAR)
		j++;
	res = ft_strsub(file, *i, j - *i);
	*i = j;
	ft_valid_opname(res) ? 0 : ft_strdel(&res);
	return (res);
}

int		ft_readarg(t_read *data, char *file, int i)
{
	char	**split;
	char	*name;
	int		tmp;
	int		j;

	j = -1;
	if (file[ft_strlen(file) - 1] == SEPARATOR_CHAR)
		return (0);
	tmp = ft_src_name(data->label->oper->name);
	split = ft_strsplit(file + i, ',');
	while ((name = ft_strtrim(split[++j])))
		if (ft_valid_arg(data, name, g_op_tab[tmp], j))
		{
			j == 0 ? data->label->oper->arg1 = name : 0;
			j == 1 ? data->label->oper->arg2 = name : 0;
			j == 2 ? data->label->oper->arg3 = name : 0;
		}
		else
		{
			ft_strdel(&name);
			ft_dstrdel(&split);
			return (0);
		}
	ft_dstrdel(&split);
	return (j == g_op_tab[tmp].nbr_args);
}

void	ft_read_arg_lb(t_read *data, char *trim, int *i)
{
	if (!data->label)
	{
		data->label = ft_new_label();
		data->label->name = ft_strdup("***");
	}
	if (!data->label->oper)
		data->label->oper = ft_new_oper();
	else
	{
		data->label->oper->next = ft_new_oper();
		data->label->oper->next->prev = data->label->oper;
		data->label->oper = data->label->oper->next;
	}
	if (!(data->label->oper->name = ft_readopername(trim, i)))
		ft_error(data, "Doesn`t valid instruction", NULL, NULL);
	if (!ft_readarg(data, trim, *i))
		ft_error(data, "Doesn`t valid parameter for instruction", NULL, NULL);
}

char	*ft_readname(t_read *data, char *file, int *i)
{
	int		j;
	char	*res;

	j = *i;
	while (file[j] && file[j] != ':')
		j++;
	!j ? ft_error(data, "Doesn`t valid label name", file, NULL) : 0;
	res = ft_strsub(file, *i, j - *i);
	*i = j + 1;
	ft_valid_label(res, 0) ? 0 : ft_strdel(&res);
	return (res);
}

void	ft_read_label(t_read *data, char *trim, int *i)
{
	if (!data->label)
		data->label = ft_new_label();
	else
	{
		data->label->oper = ft_gotoheadop(data->label->oper);
		data->label->next = ft_new_label();
		data->label->next->prev = data->label;
		data->label = data->label->next;
	}
	if (!(data->label->name = ft_readname(data, trim, i)))
		ft_error(data, "Doesn`t valid label name", trim, NULL);
}
