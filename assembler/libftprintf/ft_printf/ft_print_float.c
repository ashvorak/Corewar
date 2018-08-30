/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_float.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amazurok <amazurok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/04 19:34:34 by amazurok          #+#    #+#             */
/*   Updated: 2018/02/19 16:34:39 by amazurok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	*ft_round(t_key *key, char *str, int i)
{
	char	*ret;
	int		tmp;

	tmp = 0;
	if (i > key->precision)
		while (str[i] >= '5' || tmp)
		{
			str[--i]++;
			tmp = 0;
			if (str[i] > '9')
			{
				tmp = 1;
				str[i] = '0';
			}
			else
				break ;
		}
	ret = ft_strnew(key->precision + 1);
	ret = ft_strncat(ret, str, key->precision + 1);
	ft_strdel(&str);
	return (ret);
}

static char	*ft_addmin(char *str, int m)
{
	char	*nstr;

	if (m && str[0] != '-')
	{
		nstr = ft_strjoin("-", str);
		ft_strdel(&str);
	}
	else
		nstr = str;
	return (nstr);
}

static void	ft_prec(t_key *key, long double tmp, int m, char *bef_point)
{
	char		*aft_point;
	int			i;

	i = 1;
	aft_point = ft_strdup(".");
	if (key->precision == -1)
		key->precision = 6;
	while (i < key->precision + 2)
	{
		tmp = tmp * 10;
		aft_point = ft_realloc(aft_point, i + 1);
		aft_point[i++] = (int)tmp + '0';
		tmp = tmp - (int)tmp;
	}
	bef_point = ft_addmin(bef_point, m);
	aft_point = ft_round(key, aft_point, i - 1);
	key->res = ft_strjoin(bef_point, aft_point);
	ft_strdel(&bef_point);
	ft_strdel(&aft_point);
}

static void	ft_nprec(t_key *key, long double tmp, int m, char *bef_point)
{
	int i;

	i = ft_strlen(bef_point) - 1;
	if ((int)(tmp * 10) >= 5)
		bef_point[i]++;
	while (bef_point[i] > '9')
	{
		bef_point[i] = '0';
		bef_point[--i]++;
	}
	bef_point = ft_addmin(bef_point, m);
	key->res = bef_point;
}

void		ft_float2str(t_key *key, va_list args)
{
	char		*bef_point;
	long double	tmp;
	int			m;

	if (key->modtype->lll)
		tmp = va_arg(args, long double);
	else
		tmp = va_arg(args, double);
	m = tmp < 0 ? 1 : 0;
	bef_point = ft_ssize2a_base((ssize_t)tmp, 10);
	tmp = tmp < 0 ? -tmp : tmp;
	tmp = tmp - (ssize_t)tmp;
	if (key->precision)
		ft_prec(key, tmp, m, bef_point);
	else
		ft_nprec(key, tmp, m, bef_point);
}
