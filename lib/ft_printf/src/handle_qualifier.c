/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_qualifier.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oshvorak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/26 13:26:54 by oshvorak          #+#    #+#             */
/*   Updated: 2018/01/04 16:54:29 by oshvorak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_printf.h"

static void			parse_flag(t_spec *spec, const char *p)
{
	if (*p == '-' && !spec->flags->minus)
		spec->flags->minus = TRUE;
	else if (*p == '+')
	{
		spec->flags->plus = TRUE;
		spec->flags->space = FALSE;
	}
	else if (*p == '0')
		spec->flags->zero = TRUE;
	else if (*p == ' ' && !spec->flags->plus)
		spec->flags->space = TRUE;
	else if (*p == '#')
		spec->flags->hash = TRUE;
}

static const char	*parse_width(t_spec *spec, const char *p, va_list ap)
{
	if (*p != '*')
	{
		spec->width = ft_atoi(p);
		while (ft_isdigit(*p))
			p++;
	}
	else
	{
		spec->width = va_arg(ap, int);
		if (spec->width < 0)
		{
			spec->width = -spec->width;
			spec->flags->minus = TRUE;
		}
		p++;
	}
	return (p);
}

static const char	*parse_accuracy(t_spec *spec, const char *p, va_list ap)
{
	if (*p != '*')
	{
		if (*p == '+' || *p == '-')
		{
			parse_flag(spec, p++);
			spec->accuracy = 0;
		}
		else
		{
			spec->accuracy = ft_atoi(p);
			while (ft_isdigit(*p))
				p++;
		}
	}
	else
	{
		spec->accuracy = va_arg(ap, int);
		if (spec->accuracy < 0)
			spec->accuracy = UNDEFINED;
		p++;
	}
	return (p);
}

static const char	*parse_size(t_spec *spec, const char *p)
{
	if (*p == 'h' && *(p + 1) != 'h' && spec->size == none)
		spec->size = h;
	else if (*p == 'h' && *(p + 1) == 'h' && spec->size < hh)
		spec->size = hh;
	else if (*p == 'l' && *(p + 1) != 'l' && spec->size < l)
		spec->size = l;
	else if (*p == 'l' && *(p + 1) == 'l' && spec->size < ll)
		spec->size = ll;
	else if (*p == 'j' && spec->size < j)
		spec->size = j;
	else if (*p == 'z')
		spec->size = z;
	if (spec->size == hh || spec->size == ll)
		p++;
	p++;
	return (p);
}

const char			*handle_qualifier(const char *p, t_spec *spec, va_list ap)
{
	while (!spec->type && *p)
		if (*p == '+' || *p == '-' || *p == '0' || *p == ' ' || *p == '#')
			parse_flag(spec, p++);
		else if (ft_isdigit(*p) || *p == '*')
			p = parse_width(spec, p, ap);
		else if (*p == '.')
			p = parse_accuracy(spec, ++p, ap);
		else if (*p == 'h' || *p == 'l' || *p == 'j' || *p == 'z')
			p = parse_size(spec, p);
		else
			spec->type = *(p++);
	return (p);
}
