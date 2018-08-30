/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_unicode.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amazurok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/02 17:21:27 by amazurok          #+#    #+#             */
/*   Updated: 2018/02/04 19:41:57 by amazurok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int				ft_mod_u(wchar_t c)
{
	char	*tmp;
	int		tm;
	int		ret;

	tmp = ft_size2a_base(c, 2);
	tm = ft_strlen(tmp);
	if (tm <= 7)
		ret = 1;
	else if (tm <= 11)
		ret = 2;
	else if (tm <= 16)
		ret = 3;
	else
		ret = 4;
	ft_strdel(&tmp);
	return (ret);
}

static int		ft_myputustr(t_key *key, int s)
{
	int i;
	int size;
	int nb;

	size = 0;
	i = 0;
	while (key->wres[i])
	{
		nb = ft_mod_u(key->wres[i]);
		if (key->precision > 0 && (size + nb) <= key->precision)
			key->nwres[s++] = key->wres[i++];
		else if (key->precision < 0)
			key->nwres[s++] = key->wres[i++];
		else
			return (i);
		size += nb;
	}
	return (i);
}

static size_t	ft_ustrlen(t_key *key)
{
	size_t	i;
	size_t	size;
	int		nb;

	i = 0;
	size = 0;
	while (key->wres[i])
	{
		nb = ft_mod_u(key->wres[i]);
		if ((key->precision >= 0 && ((int)(size + nb) <= key->precision)) || \
			key->precision < 0)
			size += nb;
		else
			break ;
		i++;
	}
	return (size);
}

static int		ft_print_ustr(t_key *key)
{
	int		size;
	int		w;
	char	*res;

	key->lenr = key->wres ? ft_ustrlen(key) : 0;
	w = key->width - key->lenr;
	size = key->lenr + (w > 0 ? w : 0);
	res = ft_strnew(size);
	key->nwres = ft_myrealloc(key->nwres, size);
	if (key->flag->minus)
	{
		key->lenr = ft_myputustr(key, 0);
		ft_addchar(res, ' ', w, 0);
		key->nwres = ft_mystrcat(key->nwres, res);
	}
	else
	{
		res = key->flag->zero ? ft_addchar(res, '0', w, 0) : \
			ft_addchar(res, ' ', w, 0);
		key->nwres = ft_mystrcat(key->nwres, res);
		key->lenr = ft_myputustr(key, (w > 0 ? w : 0));
	}
	ft_strdel(&res);
	return (size);
}

int				ft_print_unic(t_key *key)
{
	unsigned int octet;

	if (key->sym == 'C' || (key->sym == 'c' && key->modtype->l))
	{
		octet = key->wr;
		return (ft_print_uchar(key, octet));
	}
	if (key->sym == 'S' || (key->sym == 's' && key->modtype->l))
	{
		if (!key->wres)
			return (ft_print_str(key));
		return (ft_print_ustr(key));
	}
	return (0);
}
