/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_key.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amazurok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/23 11:33:42 by amazurok          #+#    #+#             */
/*   Updated: 2018/06/04 12:47:30 by amazurok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "read.h"

void	ft_bzero_key(t_read *data)
{
	data->label = NULL;
	data->fd = -1;
	data->a = 0;
	data->nm = 0;
	data->cm = 0;
	data->file = NULL;
}

int		ft_set_key(t_read *data, int i, char **v)
{
	if (v[i][1] == 'a' && !v[i][2])
		data->a = 1;
	else
		ft_error(data, "Doesn`t valid key", NULL, NULL);
	return (i);
}

int		ft_read_key(int c, char **v, t_read *data)
{
	int i;

	i = 1;
	ft_bzero_key(data);
	while (i < c)
	{
		if (v[i][0] == '-' && ft_isalpha(v[i][1]))
			i = ft_set_key(data, i, v);
		i++;
	}
	return (i);
}
