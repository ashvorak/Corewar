/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_w_char.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amazurok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/02 17:04:52 by amazurok          #+#    #+#             */
/*   Updated: 2018/02/02 17:06:19 by amazurok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_print_uchar(t_key *key, unsigned int octet)
{
	int		size;
	int		w;
	char	*res;
	int		nb;

	nb = MB_CUR_MAX <= 1 ? 1 : ft_mod_u(octet);
	w = key->width - nb;
	size = w > 0 ? key->width : nb;
	res = ft_strnew(size);
	key->nwres = ft_myrealloc(key->nwres, size);
	if (key->flag->minus)
	{
		key->nwres[0] = octet ? octet : 127;
		res = ft_addchar(res, ' ', w, 0);
		key->nwres = ft_mystrcat(key->nwres, res);
	}
	else
	{
		res = key->flag->zero ? ft_addchar(res, '0', w, 0) : \
			ft_addchar(res, ' ', w, 0);
		key->nwres = ft_mystrcat(key->nwres, res);
		key->nwres[size - nb] = octet ? octet : 127;
	}
	ft_strdel(&res);
	return (size);
}
