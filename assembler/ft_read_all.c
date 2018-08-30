/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_all.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amazurok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/29 16:23:06 by amazurok          #+#    #+#             */
/*   Updated: 2018/06/16 12:50:02 by amazurok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "read.h"

char	*ft_readfile(int fd)
{
	char	buf[101];
	char	*str;
	ssize_t	ret;

	str = NULL;
	while ((ret = read(fd, buf, 100)) > 0)
	{
		buf[ret] = '\0';
		str = ft_realcat(str, buf);
	}
	return (str);
}

int		ft_cheak_double_name(t_label *lst)
{
	while (lst->next)
	{
		if (!ft_strequ(lst->name, "***"))
			if (ft_find_lbname(lst->next, lst->name))
				return (0);
		lst = lst->next;
	}
	return (1);
}

void	ft_read(t_read *data, t_header *h)
{
	char	*file;
	char	*nfile;
	size_t	k;
	int		b;

	b = 0;
	file = ft_readfile(data->fd);
	!(nfile = ft_strtrim(file)) || !nfile[0] ? \
		ft_error(data, "Empty file", file, nfile) : 0;
	k = ft_strlen(file) - 1;
	while (k > 0 && ft_space(file[k]))
	{
		if (file[k] == '\n')
			b++;
		k--;
	}
	ft_strdel(&nfile);
	!b ? ft_error(data, "Unexpected end of input", file, NULL) : 0;
	ft_read_name_com(h, data, file);
	ft_read_code(data);
	!ft_cheak_double_name(data->label) ? \
			ft_error(data, "Label name is already exist", file, NULL) : 0;
	data->file = file;
	close(data->fd);
}
