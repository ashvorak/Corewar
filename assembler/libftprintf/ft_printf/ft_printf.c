/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amazurok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/15 16:14:10 by amazurok          #+#    #+#             */
/*   Updated: 2018/02/15 16:14:13 by amazurok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int		ft_skip_key(t_key *key, const char *format)
{
	int i;

	i = 0;
	while (format[i] != key->sym)
		i++;
	i++;
	ft_del_key(key);
	return (i);
}

static char		*ft_w2s(char *str, wchar_t *w)
{
	int i;

	i = 0;
	while (w && w[i])
	{
		if (w[i] == 127)
			str[i] = 0;
		else
			str[i] = (char)w[i];
		i++;
	}
	return (str);
}

static int		set_fd(const char *format, va_list args, t_res *tres)
{
	int fd;

	if (ft_strnequ(format, "[fd]", 4))
	{
		fd = va_arg(args, int);
		if (fd > 0)
			tres->fd = fd;
		return (1);
	}
	return (0);
}

static wchar_t	*ft_rd_form(const char *format, va_list args, t_res *tres)
{
	t_key	*key;
	wchar_t *wres;

	wres = NULL;
	while (*format)
		if (*format == '%')
		{
			key = ft_new_key();
			if (!ft_check_key(key, ++format, args))
				break ;
			tres->size += ft_print_res(key, args, tres);
			tres->i += ft_wstrlen(key->nwres);
			wres = ft_myrealloc(wres, tres->i);
			wres = ft_wtrcat(wres, key->nwres);
			format += ft_skip_key(key, format);
		}
		else if (*format == '[' && set_fd(format, args, tres))
			format += 4;
		else
			wres = ft_nonpercent(&format, wres, format, tres);
	return (wres);
}

int				ft_printf(const char *format, ...)
{
	va_list	args;
	wchar_t *wres;
	char	*res;
	t_res	*tres;
	int		ret;

	tres = ft_new_tres();
	va_start(args, format);
	wres = ft_rd_form(format, args, tres);
	va_end(args);
	if (MB_CUR_MAX <= 1)
	{
		res = ft_strnew(tres->i);
		res = ft_w2s(res, wres);
		write(tres->fd, res, tres->i);
		ft_strdel(&res);
	}
	else
		ft_putustr_fd(wres, tres->fd);
	ft_wstrdel(&wres);
	ret = tres->size;
	free(tres);
	return (ret);
}
