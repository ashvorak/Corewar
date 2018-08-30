/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_digit.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amazurok <amazurok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/02 17:28:50 by amazurok          #+#    #+#             */
/*   Updated: 2018/02/19 16:30:54 by amazurok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	*ft_hash(t_key *key, char *res)
{
	if ((key->sym == 'o' || key->sym == 'O'))
		return (ft_strcat(res, "0"));
	else if (key->sym == 'x' && !(!key->precision && key->res[0] == '0'))
		return (ft_strcat(res, "0x"));
	else if (key->sym == 'X' && !(!key->precision && key->res[0] == '0'))
		return (ft_strcat(res, "0X"));
	else if (key->sym == 'p')
		return (ft_strcat(res, "0x"));
	else if (key->sym == 'b')
		return (ft_strcat(res, "0b"));
	return (res);
}

static int	ft_flg_min(t_key *key)
{
	int		size;
	int		w;
	int		p;
	char	*res;

	p = ft_precision(key);
	w = ft_width(key, p);
	size = ft_size(key, p, w);
	res = ft_strnew(size);
	res[0] = key->res[0] == '-' ? '-' : res[0];
	res[0] = key->flag->plus && key->res[0] != '-' ? '+' : res[0];
	res[0] = key->flag->space ? ' ' : res[0];
	res = key->flag->hash ? ft_hash(key, res) : res;
	res = ft_addchar(res, '0', p, 0);
	if (!(key->res[0] == '0' && !key->precision))
		res = ft_strcat(res, key->res + (res[0] == '-'));
	res = ft_addchar(res, ' ', w, 0);
	key->nwres = ft_myrealloc(key->nwres, size);
	key->nwres = ft_mystrcat(key->nwres, res);
	ft_strdel(&res);
	return (size);
}

static int	ft_flg_nmin_zero(t_key *key)
{
	int		size;
	int		w;
	int		p;
	char	*res;

	p = ft_precision(key);
	w = ft_width(key, p);
	size = ft_size(key, p, w);
	res = ft_strnew(size);
	res[0] = key->res[0] == '-' ? '-' : res[0];
	res[0] = key->flag->plus && key->res[0] != '-' ? '+' : res[0];
	res[0] = key->flag->space ? ' ' : res[0];
	res = key->flag->hash ? ft_hash(key, res) : res;
	res = ft_addchar(res, '0', w, 0);
	res = ft_addchar(res, '0', p, 0);
	if (!(key->res[0] == '0' && !key->precision))
		res = ft_strcat(res, key->res + (res[0] == '-'));
	key->nwres = ft_myrealloc(key->nwres, size);
	key->nwres = ft_mystrcat(key->nwres, res);
	ft_strdel(&res);
	return (size);
}

static int	ft_flg_nmin_nzero(t_key *key)
{
	int		size;
	int		w;
	int		p;
	char	*res;

	p = ft_precision(key);
	w = ft_width(key, p);
	size = ft_size(key, p, w);
	res = ft_strnew(size);
	res[0] = key->flag->space ? ' ' : res[0];
	res = ft_addchar(res, ' ', w, 0);
	w = w < 0 ? 0 : w;
	res[w] = key->res[0] == '-' ? '-' : res[w];
	res[w] = key->flag->plus && key->res[0] != '-' ? '+' : res[w];
	res = key->flag->hash ? ft_hash(key, res) : res;
	res = ft_addchar(res, '0', p, 0);
	if (!(key->res[0] == '0' && !key->precision))
		res = ft_strcat(res, key->res + (key->res[0] == '-'));
	key->nwres = ft_myrealloc(key->nwres, size);
	key->nwres = ft_mystrcat(key->nwres, res);
	ft_strdel(&res);
	return (size);
}

int			ft_print_dig(t_key *key)
{
	if (key->flag->minus)
		return (ft_flg_min(key));
	else if (key->flag->zero)
		return (ft_flg_nmin_zero(key));
	else
		return (ft_flg_nmin_nzero(key));
}
