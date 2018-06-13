/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_wchar.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oshvorak <oshvorak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/27 15:27:50 by oshvorak          #+#    #+#             */
/*   Updated: 2018/01/29 20:58:33 by oshvorak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_printf.h"

static int		print_width(int size, char sym, int width, int fd)
{
	while (size < width)
	{
		ft_putchar_fd(sym, fd);
		size++;
	}
	return (size);
}

int				handle_wchar(wchar_t c, t_spec *spec)
{
	int		size;
	int		bits;
	char	sym;

	size = 0;
	bits = active_bits(c);
	if (spec->flags->minus)
	{
		size += size_char(bits);
		ft_putwchar(c, bits, spec->fd);
		size = print_width(size, ' ', spec->width, spec->fd);
	}
	else
	{
		sym = (spec->flags->zero) ? '0' : ' ';
		size += size_char(bits);
		size = print_width(size, sym, spec->width, spec->fd);
		ft_putwchar(c, bits, spec->fd);
	}
	return (size);
}
