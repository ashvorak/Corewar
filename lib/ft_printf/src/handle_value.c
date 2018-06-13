/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_value.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oshvorak <oshvorak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/27 15:27:41 by oshvorak          #+#    #+#             */
/*   Updated: 2018/02/05 17:39:49 by oshvorak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_printf.h"

static int	parse_char(t_spec *spec, va_list ap)
{
	int size;

	if ((spec->type == 'C' || (spec->type == 'c' && spec->size == l)))
	{
		if (MB_CUR_MAX > 1)
			size = handle_wchar(va_arg(ap, wint_t), spec);
		else
			size = handle_char(va_arg(ap, int), spec);
	}
	else if (spec->type == '%')
		size = handle_char('%', spec);
	else
		size = handle_char(va_arg(ap, int), spec);
	return (size);
}

static int	parse_int(t_spec *spec, va_list ap)
{
	int		size;
	char	*v;

	v = NULL;
	if (spec->size == none && spec->type != 'D')
		v = convert_int(va_arg(ap, int));
	else if (spec->type == 'D')
		v = convert_int(va_arg(ap, long int));
	else if (spec->size == hh)
		v = convert_int((signed char)va_arg(ap, int));
	else if (spec->size == h)
		v = convert_int((short int)va_arg(ap, int));
	else if (spec->size == l)
		v = convert_int(va_arg(ap, long int));
	else if (spec->size == ll)
		v = convert_int(va_arg(ap, long long int));
	else if (spec->size == j)
		v = convert_int(va_arg(ap, intmax_t));
	else if (spec->size == z)
		v = convert_int(va_arg(ap, ssize_t));
	size = handle_num(v, spec);
	(v) ? free(v) : 0;
	return (size);
}

static int	parse_base(t_spec *spec, va_list ap)
{
	int		size;
	char	*v;

	v = NULL;
	if (spec->type == 'p' || spec->type == 'b')
		v = convert_base((size_t)va_arg(ap, void*), spec);
	else if (spec->size == none && is_type("oxXup", spec->type))
		v = convert_base(va_arg(ap, unsigned int), spec);
	else if (is_type("OU", spec->type))
		v = convert_base(va_arg(ap, unsigned long int), spec);
	else if (spec->size == hh)
		v = convert_base((unsigned char)va_arg(ap, unsigned int), spec);
	else if (spec->size == h)
		v = convert_base((unsigned short int)va_arg(ap, unsigned int), spec);
	else if (spec->size == l)
		v = convert_base(va_arg(ap, unsigned long int), spec);
	else if (spec->size == ll)
		v = convert_base(va_arg(ap, unsigned long long int), spec);
	else if (spec->size == j)
		v = convert_base(va_arg(ap, uintmax_t), spec);
	else if (spec->size == z)
		v = convert_base(va_arg(ap, size_t), spec);
	size = handle_num(v, spec);
	(v) ? free(v) : 0;
	return (size);
}

static int	parse_float(t_spec *spec, va_list ap)
{
	int		size;
	char	*v;

	v = NULL;
	v = convert_float(va_arg(ap, double), spec);
	size = handle_float(v, spec);
	(v) ? free(v) : 0;
	return (size);
}

int			handle_value(t_spec *spec, va_list ap, int len)
{
	int	size;

	size = 0;
	if (is_type("cC%", spec->type))
		size = parse_char(spec, ap);
	else if (is_type("dDi", spec->type))
		size = parse_int(spec, ap);
	else if (is_type("oOxXuUpb", spec->type))
		size = parse_base(spec, ap);
	else if (spec->type == 's' && spec->size != l)
		size = handle_str(va_arg(ap, char*), spec);
	else if (spec->type == 'S' || (spec->type == 's' && spec->size == l))
		size = handle_wstr(va_arg(ap, wchar_t*), spec);
	else if (is_type("fF", spec->type))
		size = parse_float(spec, ap);
	else if (spec->type == 'n')
		handle_n(spec, len, ap);
	else if (spec->type)
		size = handle_char(spec->type, spec);
	free(spec->flags);
	free(spec);
	return (size);
}
