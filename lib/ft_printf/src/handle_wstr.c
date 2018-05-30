/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_wstr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oshvorak <oshvorak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/27 15:27:59 by oshvorak          #+#    #+#             */
/*   Updated: 2018/01/30 13:43:43 by oshvorak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_printf.h"

static int	str_print(wchar_t *value, t_spec *spec)
{
	int i;
	int j;
	int bits;

	i = 0;
	while (*value)
	{
		bits = active_bits(*value);
		j = size_char(bits);
		if (i + j <= spec->accuracy || spec->accuracy == UNDEFINED)
		{
			ft_putwchar(*value++, bits, spec->fd);
			i += j;
		}
		else
			break ;
	}
	return (i);
}

static int	parse_width(wchar_t *value, t_spec *spec)
{
	int		i;
	int		j;
	int		size;
	char	sym;

	i = 0;
	size = 0;
	sym = (spec->flags->zero) ? '0' : ' ';
	while (*value)
	{
		j = size_char(active_bits(*value));
		if (i + j <= spec->accuracy || spec->accuracy == UNDEFINED)
		{
			i += j;
			value++;
		}
		else
			break ;
	}
	while (size < spec->width - i)
	{
		ft_putchar_fd(sym, spec->fd);
		size++;
	}
	return (size);
}

int			handle_wstr(wchar_t *value, t_spec *spec)
{
	int size;

	size = 0;
	if (!value)
		return (handle_str((char*)value, spec));
	if (spec->flags->minus)
	{
		size += str_print(value, spec);
		while (size < spec->width)
		{
			ft_putchar_fd(' ', spec->fd);
			size++;
		}
	}
	else
	{
		size += parse_width(value, spec);
		size += str_print(value, spec);
	}
	return (size);
}
