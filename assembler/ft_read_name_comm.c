/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_name_comm.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amazurok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/29 16:24:13 by amazurok          #+#    #+#             */
/*   Updated: 2018/06/07 16:33:53 by amazurok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "read.h"

int		ft_read_name(t_read *data, t_header *h, char *file, int i)
{
	int j;

	j = 0;
	data->nm ? ft_error(data, "More then one name", NULL, NULL) : 0;
	data->nm = 1;
	while (file[i] && file[i] != '\"')
	{
		if (file[i] != ' ' && file[i] != '\t')
			ft_error(data, "Name error", NULL, NULL);
		i++;
	}
	i++;
	while (file[i] != '\"')
	{
		if (j > PROG_NAME_LENGTH)
			ft_error(data, "Name too long (Max length 128)", NULL, NULL);
		h->prog_name[j++] = file[i++];
	}
	return (i);
}

int		ft_read_comm(t_read *data, t_header *h, char *file, int i)
{
	int j;

	j = 0;
	data->cm ? ft_error(data, "More then one comment", NULL, NULL) : 0;
	data->cm = 1;
	while (file[i] && file[i] != '\"')
	{
		if (file[i] != ' ' && file[i] != '\t')
			ft_error(data, "Comment error", NULL, NULL);
		i++;
	}
	i++;
	while (file[i] != '\"')
	{
		if (j > COMMENT_LENGTH)
			ft_error(data, "Comment too long (Max length 2048)", NULL, NULL);
		h->comment[j++] = file[i++];
	}
	return (i);
}

void	ft_read_name_com(t_header *h, t_read *data, char *file)
{
	int		i;

	i = 0;
	ft_bzero(h->comment, COMMENT_LENGTH + 1);
	ft_bzero(h->prog_name, PROG_NAME_LENGTH + 1);
	while (file[i] && (!data->nm || !data->cm))
	{
		if (ft_strnequ(file + i, NAME_CMD_STRING, 5))
			i = ft_read_name(data, h, file, i + 5);
		else if (ft_strnequ(file + i, COMMENT_CMD_STRING, 8))
			i = ft_read_comm(data, h, file, i + 8);
		else if (file[i] == COMMENT_CHAR || file[i] == ';')
			i = ft_go2end(file, i);
		else if (!ft_space(file[i]))
			ft_error(data, "Name/Comment error", file, NULL);
		i++;
	}
	lseek(data->fd, (long)i, SEEK_SET);
}
