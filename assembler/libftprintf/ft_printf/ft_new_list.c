/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_new_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amazurok <amazurok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/23 12:22:06 by amazurok          #+#    #+#             */
/*   Updated: 2018/02/19 16:32:26 by amazurok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_res				*ft_new_tres(void)
{
	t_res	*tres;

	tres = (t_res *)malloc(sizeof(t_res));
	tres->i = 0;
	tres->size = 0;
	tres->fd = 1;
	return (tres);
}

static t_modtype	*ft_newmodt(void)
{
	t_modtype *modtype;

	modtype = (t_modtype *)malloc(sizeof(t_modtype));
	modtype->h = 0;
	modtype->hh = 0;
	modtype->l = 0;
	modtype->ll = 0;
	modtype->j = 0;
	modtype->z = 0;
	modtype->lll = 0;
	modtype->t = 0;
	return (modtype);
}

static t_flag		*ft_new_flag(void)
{
	t_flag *flag;

	flag = (t_flag *)malloc(sizeof(t_flag));
	flag->space = 0;
	flag->plus = 0;
	flag->minus = 0;
	flag->zero = 0;
	flag->hash = 0;
	return (flag);
}

t_key				*ft_new_key(void)
{
	t_key *key;

	key = (t_key *)malloc(sizeof(t_key));
	key->flag = ft_new_flag();
	key->width = 0;
	key->precision = -1;
	key->modtype = ft_newmodt();
	key->sym = 0;
	key->r = 0;
	key->lenr = 0;
	key->res = NULL;
	key->wres = NULL;
	key->nwres = NULL;
	return (key);
}
