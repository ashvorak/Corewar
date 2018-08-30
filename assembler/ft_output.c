/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_output.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amazurok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/29 12:56:43 by aryabenk          #+#    #+#             */
/*   Updated: 2018/06/12 16:59:30 by amazurok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_write.h"

char	*ft_create_filename(char *name)
{
	char	*res;
	char	*tmp;

	tmp = name;
	name = ft_strrchr(name, '/');
	name = name ? name + 1 : tmp;
	res = ft_strsub(name, 0, ft_strlen(name) - 1);
	res = ft_realcat(res, "cor");
	return (res);
}

void	ft_print_result(char *filename, t_uchar *res, ssize_t size)
{
	int		fd;
	char	*new;

	new = ft_create_filename(filename);
	fd = open(new, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	write(fd, res, size);
	ft_printf("Writing output program %s to %s\n", filename, new);
	ft_strdel(&new);
	close(fd);
}
