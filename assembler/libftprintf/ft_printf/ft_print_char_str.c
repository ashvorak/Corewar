/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_char_str.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amazurok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/02 16:57:09 by amazurok          #+#    #+#             */
/*   Updated: 2018/02/02 16:59:05 by amazurok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_print_char(t_key *key)
{
	int		size;
	int		w;
	char	*res;

	w = key->width - 1;
	size = w > 0 ? key->width : 1;
	res = ft_strnew(size);
	key->nwres = ft_myrealloc(key->nwres, size);
	if (key->flag->minus)
	{
		res[0] = key->r ? key->r : 127;
		res = ft_addchar(res, ' ', w, 1);
		key->nwres = ft_mystrncat(key->nwres, res, size);
	}
	else
	{
		res = key->flag->zero ? ft_addchar(res, '0', w, 0) : \
			ft_addchar(res, ' ', w, 0);
		res[size - 1] = (key->r ? key->r : 127);
		key->nwres = ft_mystrncat(key->nwres, res, size);
	}
	ft_strdel(&res);
	return (size);
}

int		ft_print_str(t_key *key)
{
	int		size;
	int		w;
	int		p;
	char	*res;

	p = key->precision;
	key->lenr = p < key->lenr && p >= 0 ? p : key->lenr;
	w = key->width - key->lenr;
	size = key->lenr + (w > 0 ? w : 0);
	res = ft_strnew(size);
	if (key->flag->minus)
	{
		res = key->res ? ft_strncat(res, key->res, key->lenr) : res;
		res = ft_addchar(res, ' ', w, 0);
	}
	else
	{
		res = key->flag->zero ? ft_addchar(res, '0', w, 0) : \
			ft_addchar(res, ' ', w, 0);
		res = key->res ? ft_strncat(res, key->res, key->lenr) : res;
	}
	key->nwres = ft_myrealloc(key->nwres, size);
	key->nwres = ft_mystrcat(key->nwres, res);
	ft_strdel(&res);
	return (size);
}
