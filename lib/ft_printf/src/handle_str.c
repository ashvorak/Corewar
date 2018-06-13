/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_str.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oshvorak <oshvorak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/27 15:27:32 by oshvorak          #+#    #+#             */
/*   Updated: 2018/01/30 13:38:05 by oshvorak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_printf.h"

static int	str_print(char *value, int len, int fd)
{
	int i;

	i = 0;
	while (i < len && *value)
		i++;
	write(fd, &(*value), i);
	return (i);
}

static int	parse_width(int len, t_spec *spec)
{
	int		size;
	char	sym;

	size = 0;
	sym = (spec->flags->zero) ? '0' : ' ';
	spec->width -= len;
	while (size < spec->width)
	{
		ft_putchar_fd(sym, spec->fd);
		size++;
	}
	return (size);
}

int			handle_str(char *value, t_spec *spec)
{
	int len;
	int size;

	size = 0;
	value = (!value) ? "(null)" : value;
	len = ft_strlen(value);
	if (spec->flags->minus)
	{
		if (spec->accuracy != UNDEFINED)
			len = (len > spec->accuracy) ? spec->accuracy : len;
		size += str_print(value, len, spec->fd);
		while (size < spec->width)
		{
			ft_putchar_fd(' ', spec->fd);
			size++;
		}
	}
	else
	{
		if (spec->accuracy != UNDEFINED)
			len = (len > spec->accuracy) ? spec->accuracy : len;
		size += parse_width(len, spec);
		size += str_print(value, len, spec->fd);
	}
	return (size);
}
