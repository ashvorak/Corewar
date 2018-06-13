/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_char.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oshvorak <oshvorak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/27 15:27:19 by oshvorak          #+#    #+#             */
/*   Updated: 2018/02/05 18:57:49 by oshvorak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_printf.h"

int	handle_char(char c, t_spec *spec)
{
	int		size;
	char	sym;

	size = 0;
	if (spec->flags->minus)
	{
		ft_putchar_fd(c, spec->fd);
		while (++size < spec->width)
			ft_putchar_fd(' ', spec->fd);
	}
	else
	{
		sym = (spec->flags->zero) ? '0' : ' ';
		while (++size < spec->width)
			ft_putchar_fd(sym, spec->fd);
		ft_putchar_fd(c, spec->fd);
	}
	return (size);
}
