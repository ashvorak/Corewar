/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oshvorak <oshvorak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/22 16:45:17 by oshvorak          #+#    #+#             */
/*   Updated: 2018/02/05 20:10:00 by oshvorak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_printf.h"

int	g_size;
int	g_fd;

static t_spec		*spec_new(int fd)
{
	t_spec	*spec;

	if (!(spec = (t_spec*)malloc(sizeof(t_spec))))
		return (NULL);
	if (!(spec->flags = (t_flags*)malloc(sizeof(t_flags))))
		return (NULL);
	spec->flags->minus = FALSE;
	spec->flags->plus = FALSE;
	spec->flags->zero = FALSE;
	spec->flags->space = FALSE;
	spec->flags->hash = FALSE;
	spec->width = UNDEFINED;
	spec->accuracy = UNDEFINED;
	spec->size = none;
	spec->type = none;
	spec->fd = fd;
	return (spec);
}

static t_spec		*fix(t_spec *spec)
{
	if (spec->type == 'p')
		spec->flags->hash = TRUE;
	else if (!is_type("oOxXp", spec->type))
		spec->flags->hash = FALSE;
	if (!is_type("dDifF", spec->type))
	{
		spec->flags->space = FALSE;
		spec->flags->plus = FALSE;
	}
	return (spec);
}

static const char	*make_colors_fd(const char *format, va_list ap)
{
	int			i;
	const char	*p;
	char		*s;

	i = 0;
	p = format;
	while (p[i] != '}' && p[i])
		i++;
	(p[i + 1]) ? i++ : 0;
	s = ft_strsub(format, 0, i);
	if (!ft_strcmp(s, "{fd}"))
	{
		g_fd = va_arg(ap, int);
		format = &p[i];
	}
	else if (make_colors(s, g_fd))
		format = &p[i];
	else
	{
		ft_putchar_fd(*(format++), g_fd);
		g_size++;
	}
	(s) ? free(s) : 0;
	return (format);
}

int					ft_printf(const char *format, ...)
{
	t_spec	*spec;
	va_list	ap;

	g_fd = 1;
	g_size = 0;
	va_start(ap, format);
	while (*format)
	{
		if (*format == '%')
		{
			spec = spec_new(g_fd);
			format = handle_qualifier(++format, spec, ap);
			g_size += handle_value(fix(spec), ap, g_size);
		}
		else if (*format == '{')
			format = make_colors_fd(format, ap);
		else
		{
			ft_putchar_fd(*format++, g_fd);
			g_size++;
		}
	}
	va_end(ap);
	return (g_size);
}
