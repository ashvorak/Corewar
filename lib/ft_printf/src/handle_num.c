/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_num.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oshvorak <oshvorak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/27 15:27:25 by oshvorak          #+#    #+#             */
/*   Updated: 2018/02/05 19:12:18 by oshvorak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_printf.h"

static int	parse_flags(char *v, t_spec *spec, int fd)
{
	if (*v == '-' || spec->flags->plus || spec->flags->space)
	{
		if (*v == '-' || spec->flags->plus)
			(*v == '-') ? ft_putchar_fd('-', fd) : ft_putchar_fd('+', fd);
		else
			ft_putchar_fd(' ', fd);
		return (1);
	}
	else if (spec->flags->hash)
	{
		if (is_type("oO", spec->type))
			if (*v != '0' || spec->accuracy == 0)
			{
				ft_putchar_fd('0', fd);
				return (1);
			}
		if (is_type("xXp", spec->type))
			if (*v != '0' || spec->type == 'p')
			{
				(spec->type == 'X') ? write(fd, "0X", 2) \
				: write(fd, "0x", 2);
				return (2);
			}
	}
	return (0);
}

static int	parse_accuracy(int len, t_spec *spec, char *v)
{
	int size;
	int end;

	size = 0;
	end = spec->accuracy - len;
	if (spec->flags->hash && (is_type("oO", spec->type)) && *v != '0')
		end--;
	while (size < end)
	{
		ft_putchar_fd('0', spec->fd);
		size++;
	}
	return (size);
}

static int	take_end(char *v, t_spec *spec, int size, int end)
{
	if (*v == '0' && spec->accuracy == 0)
		end++;
	if (size == 0 && *v != '0' && is_type("oO", spec->type) && \
	spec->flags->hash && (spec->accuracy == 0 || spec->accuracy == UNDEFINED))
		end--;
	else if (size == 0 && spec->flags->hash && \
	(*v != '0' || spec->type == 'p') && (is_type("xXp", spec->type)))
		end -= 2;
	else if ((spec->flags->plus || spec->flags->space || *v == '-')\
	&& (!spec->flags->zero || spec->accuracy >= 0))
		end--;
	return (end);
}

static int	parse_width(char *v, t_spec *spec, int len)
{
	int		size;
	int		end;
	char	sym;

	size = 0;
	if (spec->flags->zero && spec->accuracy < 0)
		size = parse_flags(v, spec, spec->fd);
	sym = (spec->flags->zero && spec->accuracy < 0) ? '0' : ' ';
	len = spec->accuracy > len ? spec->accuracy : len;
	end = take_end(v, spec, size, spec->width - len);
	while (size < end)
	{
		ft_putchar_fd(sym, spec->fd);
		size++;
	}
	if (!spec->flags->zero || spec->accuracy >= 0)
		size += parse_flags(v, spec, spec->fd);
	return (size);
}

int			handle_num(char *v, t_spec *spec)
{
	int len;
	int size;

	size = 0;
	len = (*v != '-') ? ft_strlen(v) : ft_strlen(v) - 1;
	if (spec->flags->minus)
	{
		size += parse_flags(v, spec, spec->fd);
		size += parse_accuracy(len, spec, v);
		(*v == '-') ? v++ : 0;
		(*v == '0' && spec->accuracy == 0) ? len-- : write(spec->fd, v, len);
		while (size < spec->width - len)
		{
			ft_putchar_fd(' ', spec->fd);
			size++;
		}
	}
	else
	{
		size += parse_width(v, spec, len);
		(*v == '-') ? v++ : 0;
		size += parse_accuracy(len, spec, v);
		(*v == '0' && spec->accuracy == 0) ? size-- : write(spec->fd, v, len);
	}
	return (size += ft_strlen(v));
}
